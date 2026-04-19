#include "olam.h"

#include <QApplication>
#include <QClipboard>
#include <QCompleter>
#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QLocale>
#include <QMessageBox>
#include <QSettings>
#include <QShortcut>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStyleHints>
#include <QSystemTrayIcon>
#include <QTextToSpeech>

#include "about.h"
#include "olamdatabase.h"
#include "ui_olam.h"

// ── Helpers ──────────────────────────────────────────────────────────────────

static QString getResourcePath() {
    if (QDir("db").exists()) return "./db";
#if defined(Q_OS_WIN)
    return QApplication::applicationDirPath() + "/db";
#elif defined(Q_OS_MACOS)
    return QDir::cleanPath(QApplication::applicationDirPath() + "/../Resources");
#elif defined(Q_OS_LINUX)
    return QDir::cleanPath(QApplication::applicationDirPath() + "/../share/olam/data/db");
#else
    return QApplication::applicationDirPath() + "/db";
#endif
}

static QString getOlamDbPath()  { return getResourcePath() + "/olamdb.db"; }
static QString getDatukDbPath() { return getResourcePath() + "/datuk.sqlite"; }

// ── Construction ─────────────────────────────────────────────────────────────

Olam::Olam(QWidget *parent) : QMainWindow(parent), ui(new Ui::Olam) {
    ui->setupUi(this);
    createConnection();

    // Apply saved theme, falling back to system preference
    {
        QSettings s;
        bool dark = s.contains("darkMode")
                        ? s.value("darkMode").toBool()
                        : QApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
        applyTheme(dark);
    }

    // Follow OS theme changes when no manual override is stored
    connect(QApplication::styleHints(), &QStyleHints::colorSchemeChanged,
            this, [this](Qt::ColorScheme scheme) {
        if (!QSettings().contains("darkMode")) {
            applyTheme(scheme == Qt::ColorScheme::Dark);
        }
    });

    ui->dict_result->setOpenLinks(false);
    connect(ui->dict_result, SIGNAL(anchorClicked(QUrl)), this, SLOT(handleLink(QUrl)));

    // Cmd+L / Ctrl+L — focus search field
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_L), this, [this]() {
        ui->mal_eng->setCurrentIndex(0);
        ui->dict_word->setFocus();
        ui->dict_word->selectAll();
    });

    showWordOfTheDay();
    setupTrayIcon();
}

Olam::~Olam() { delete ui; }

// ── Theme ─────────────────────────────────────────────────────────────────────

void Olam::applyTheme(bool dark) {
    m_isDark = dark;
    QSettings().setValue("darkMode", dark);

    QFile f(dark ? ":/resources/style_dark" : ":/resources/style");
    if (f.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(QString::fromUtf8(f.readAll()));
    } else {
        qWarning() << "applyTheme: could not load stylesheet";
    }

    updateResultStylesheets();
    ui->action_DarkMode->setChecked(dark);
}

void Olam::updateResultStylesheets() {
    const QString fg       = m_isDark ? "#f5f5f7" : "#1d1d1f";
    const QString divider  = m_isDark ? "#3a3a3c" : "#f2f2f7";
    const QString link     = m_isDark ? "#0a84ff" : "#0071e3";
    const QString hdrColor = m_isDark ? "#98989d" : "#86868b";
    const QString hdrBorder= m_isDark ? "#3a3a3c" : "#e5e5ea";

    const QString css =
        "body { margin: 4px; color: " + fg + "; }"
        "a { color: " + link + "; text-decoration: none; }"
        "ul { margin: 0; padding: 0; list-style: none; }"
        "li { padding: 6px 2px; font-size: 16px; border-bottom: 1px solid " + divider + "; }"
        "li:last-child { border-bottom: none; }"
        ".pos { color: " + hdrColor + "; font-size: 11px; font-weight: bold; "
        "text-transform: uppercase; letter-spacing: 1px; "
        "padding: 10px 2px 4px; border-bottom: 1px solid " + hdrBorder + "; }";

    ui->dict_result->document()->setDefaultStyleSheet(css);
    ui->corpus_result->document()->setDefaultStyleSheet(css);
}

void Olam::on_action_DarkMode_triggered() {
    applyTheme(!m_isDark);
}

// ── Database connection ───────────────────────────────────────────────────────

bool Olam::createConnection() {
    auto openDb = [](const QString &name, const QString &path) -> bool {
        QSqlDatabase db;
        if (QSqlDatabase::contains(name)) {
            db = QSqlDatabase::database(name);
        } else {
            db = QSqlDatabase::addDatabase("QSQLITE", name);
            db.setDatabaseName(path);
        }
        if (db.isOpen()) return true;

        if (!QFileInfo::exists(path))
            qCritical() << "createConnection: file not found:" << path;

        bool ok = db.open();
        if (!ok) qCritical() << "createConnection: failed to open" << name << db.lastError().text();
        else     qDebug()    << "createConnection: opened" << name << "at" << path;
        return ok;
    };

    bool olamOk  = openDb("olam",  getOlamDbPath());
    bool datukOk = openDb("datuk", getDatukDbPath());
    bool ok = olamOk && datukOk;
    if (!ok) QMessageBox::critical(nullptr, "Database error",
                                   QSqlDatabase::database("olam").lastError().text());
    return ok;
}

// ── Tray icon ─────────────────────────────────────────────────────────────────

void Olam::setupTrayIcon() {
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    QMenu *menu = new QMenu(this);
    QIcon icon(":/resources/logo");
    try {
        trayIcon->setIcon(icon);
        window()->setWindowIcon(icon);
        trayIcon->setToolTip("Olam — English Malayalam Dictionary");
        menu->addAction("About", new About, SLOT(show()));
        menu->addAction("Help",  this,      SLOT(openHelpUrl()));
        menu->addSeparator();
        menu->addAction("Exit", QApplication::instance(), SLOT(quit()));
        trayIcon->setContextMenu(menu);
        trayIcon->show();
    } catch (std::exception &e) {
        qWarning() << "setupTrayIcon:" << e.what();
    }
}

void Olam::openHelpUrl() {
    QDesktopServices::openUrl(QUrl("https://github.com/tachyons/olam"));
}

// ── Word of the day ───────────────────────────────────────────────────────────

void Olam::showWordOfTheDay() {
    QSqlDatabase db = QSqlDatabase::database("olam");
    if (!db.isOpen()) return;

    QSqlQuery query(db);
    query.prepare("SELECT english FROM dictionary "
                  "WHERE english != '' AND malayalam != '' "
                  "ORDER BY RANDOM() LIMIT 1");
    if (!query.exec() || !query.next()) return;

    const QString word = query.value(0).toString();
    ui->dict_word->setText(word);
    ui->dict_result->setHtml(
        "<div class='pos'>Word of the Day</div>" + lookupWord(word));
}

// ── Search history ────────────────────────────────────────────────────────────

void Olam::addToHistory(const QString &word) {
    if (word.trimmed().isEmpty()) return;
    QSettings s;
    QStringList history = s.value("searchHistory").toStringList();
    history.removeAll(word);
    history.prepend(word);
    if (history.size() > 20) history = history.mid(0, 20);
    s.setValue("searchHistory", history);
}

// ── Copy ──────────────────────────────────────────────────────────────────────

static QString stripLinks(const QString &text) {
    // Remove " [→]" and " [►]" link markers from OlamWord::wordLink/soundLink.
    // Use plain string removal with C++ \u escapes — regex raw literals don't
    // process \u, and QTextBrowser::toPlainText() yields the actual characters.
    QString s = text;
    s.remove(QString(" [\u2192]"));   // translate link  [→]
    s.remove(QString(" [\u25b6]"));   // speak link      [►]
    return s.trimmed();
}

void Olam::on_copy_dict_clicked() {
    QApplication::clipboard()->setText(stripLinks(ui->dict_result->toPlainText()));
}

void Olam::on_copy_corpus_clicked() {
    QApplication::clipboard()->setText(stripLinks(ui->corpus_result->toPlainText()));
}

// ── Dictionary lookup ─────────────────────────────────────────────────────────

QString Olam::lookupWord(const QString &rawWord) {
    QSqlDatabase db = QSqlDatabase::database("olam");
    if (!db.isOpen() && !db.open()) {
        qCritical() << "lookupWord: cannot open db:" << db.lastError().text();
        return {};
    }

    QString word = rawWord.trimmed();
    if (word.isEmpty()) return {};
    word = word.left(1).toUpper() + word.mid(1);

    const QString lang = OlamDatabase::detect_language(word);
    qDebug() << "lookupWord:" << word << "lang:" << lang;

    QSqlQuery query(db);
    if (lang == "eng") {
        query.prepare("SELECT malayalam, types FROM dictionary WHERE english = ?");
    } else {
        query.prepare("SELECT english, types FROM dictionary WHERE malayalam = ?");
    }
    query.addBindValue(word);

    if (!query.exec()) {
        qCritical() << "lookupWord: query failed:" << query.lastError().text();
        return {};
    }

    QList<OlamWord> words;
    while (query.next())
        words.append(OlamWord(query.value(0).toString(), query.value(1).toString()));

    qDebug() << "lookupWord: found" << words.size() << "results";

    QList<OlamWord> noun, verb, adj, adverb, other;
    for (const OlamWord &w : words) {
        if      (w.pos == "n")   noun   << w;
        else if (w.pos == "v")   verb   << w;
        else if (w.pos == "a")   adj    << w;
        else if (w.pos == "adv") adverb << w;
        else                     other  << w;
    }

    QString result;
    result += printpos("Noun",      noun);
    result += printpos("Verb",      verb);
    result += printpos("Adverb",    adverb);
    result += printpos("Adjective", adj);
    result += printpos("Other",     other);

    if (result.isEmpty()) result = "<li>No results found</li>";
    return result;
}

QString Olam::printpos(const QString &pos, const QList<OlamWord> &wordlist) {
    if (wordlist.isEmpty()) return {};
    QString out = "<div class='pos'>" + pos + "</div><ul>";
    for (const OlamWord &w : wordlist) out += w.toS();
    out += "</ul>";
    return out;
}

// ── UI slots ──────────────────────────────────────────────────────────────────

void Olam::on_maleng_search_clicked() {
    qDebug() << "on_maleng_search_clicked";
    const QString word = ui->dict_word->text();
    addToHistory(word);
    const QString result = lookupWord(word);
    ui->dict_result->setHtml(result.isEmpty()
        ? "<li>No results found</li>" : result);
}

void Olam::on_dict_word_returnPressed() {
    on_maleng_search_clicked();
}

void Olam::on_malmal_search_clicked() {
    qDebug() << "on_malmal_search_clicked";
    ui->corpus_result->setHtml(searchcorpus(ui->corpus_word->text()).trimmed());
}

void Olam::on_corpus_word_returnPressed() {
    on_malmal_search_clicked();
}

void Olam::on_dict_word_textEdited(const QString &) {
    const QString word = ui->dict_word->text().trimmed();
    QStringList suggestions;
    if (word.isEmpty()) {
        suggestions = QSettings().value("searchHistory").toStringList();
    } else {
        suggestions = OlamDatabase().suggestions(word);
    }
    QCompleter *c = new QCompleter(suggestions, this);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    ui->dict_word->setCompleter(c);
}

void Olam::on_corpus_word_textEdited(const QString &) {
    QSqlDatabase db = QSqlDatabase::database("datuk");
    if (!db.isOpen() && !db.open()) return;

    const QString word = ui->corpus_word->text().trimmed();
    QSqlQuery query(db);
    query.prepare("SELECT DISTINCT word FROM word WHERE word LIKE ? LIMIT 10");
    query.addBindValue(word + "%");
    if (!query.exec()) {
        qWarning() << "corpus autocomplete failed:" << query.lastError().text();
        return;
    }

    QStringList list;
    while (query.next()) list << query.value(0).toString();

    QCompleter *c = new QCompleter(list, this);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    ui->corpus_word->setCompleter(c);
}

// ── Link handling ─────────────────────────────────────────────────────────────

void Olam::handleLink(QUrl link) {
    const QString raw = link.toString();
    qDebug() << "handleLink(QUrl):" << raw;

    const int sep = raw.indexOf(':');
    if (sep < 0) { qWarning() << "handleLink: no ':' in URL"; return; }

    const QString action = raw.left(sep);
    const QString word   = raw.mid(sep + 1);

    if (action == "translate") {
        ui->dict_word->setText(word);
        on_maleng_search_clicked();
    } else if (action == "speak") {
        qDebug() << "speaking:" << word;
        QTextToSpeech *tts = new QTextToSpeech(this);
        tts->setLocale(QLocale::Malayalam);
        tts->say(word);
    } else {
        qWarning() << "handleLink: unknown action" << action;
    }
}

// ── Corpus search ─────────────────────────────────────────────────────────────

QString Olam::searchcorpus(const QString &rawWord) {
    const QString word = rawWord.trimmed();
    qDebug() << "searchcorpus:" << word;

    QSqlDatabase db = QSqlDatabase::database("datuk");
    if (!db.isOpen() && !db.open()) {
        qCritical() << "searchcorpus: cannot open datuk db";
        return "<li>Database unavailable</li>";
    }

    QSqlQuery query(db);
    query.prepare(
        "SELECT definition, rtype, letter FROM word, relation, definition "
        "WHERE word.id = relation.id_word "
        "AND relation.id_definition = definition.id "
        "AND word.word = ?");
    query.addBindValue(word);

    if (!query.exec()) {
        qCritical() << "searchcorpus: query failed:" << query.lastError().text();
        return "<li>Query failed</li>";
    }

    QString result = "<ul>";
    while (query.next()) {
        result += "<li>" + query.value(0).toString()
                + " <b>" + query.value(1).toString() + "</b></li>";
    }
    result += "</ul>";

    if (result == "<ul></ul>") result = "<li>No results found</li>";
    return result;
}

// ── Menu actions ──────────────────────────────────────────────────────────────

void Olam::on_action_About_triggered() {
    About *d = new About(this);
    d->setAttribute(Qt::WA_DeleteOnClose);
    d->show();
}

void Olam::on_action_Exit_triggered() { qApp->quit(); }
