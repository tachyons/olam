#include "olam.h"

#include <QCompleter>
#include <QDesktopServices>
#include <QDir>
#include <QFileInfo>
#include <QLocale>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSystemTrayIcon>
#include <QTextToSpeech>

#include "about.h"
#include "olamdatabase.h"
#include "ui_olam.h"

void Olam::setupTrayIcon() {
  QSystemTrayIcon *trayIcon = new QSystemTrayIcon;
  QMenu *trayIconMenu = new QMenu;
  QIcon icon = QIcon(":/resources/logo");
  try {
    trayIcon->setIcon(icon);
    window()->setWindowIcon(icon);
    trayIcon->setToolTip("Unofficial Olam English Malayalam Dictionary");
    trayIconMenu->addAction("About", new About, SLOT(show()));
    trayIconMenu->addAction("Help", this, SLOT(openHelpUrl()));
    trayIconMenu->addSeparator();
    trayIconMenu->addAction("Exit", QApplication::instance(), SLOT(quit()));
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();
  } catch (std::exception &e) {
    qWarning() << "Failed to initialize tray icon:" << e.what();
  }
}

void Olam::openHelpUrl() {
  QDesktopServices::openUrl(QUrl("https://github.com/tachyons/olam"));
}

Olam::Olam(QWidget *parent) : QMainWindow(parent), ui(new Ui::Olam) {
  ui->setupUi(this);
  createConnection();
  ui->dict_result->setFontPointSize(100);
  QFont font;
  font.setPixelSize(20);
  ui->dict_result->setFont(font);

  ui->dict_result->setOpenLinks(false);
  QObject::connect(ui->dict_result, SIGNAL(anchorClicked(QUrl)), this,
                   SLOT(handleLink(QUrl)));

  setupTrayIcon();
}

Olam::~Olam() { delete ui; }

static QString getResourcePath() {
  if (QDir("db").exists()) {
    return "./db";
  }
#if defined(Q_OS_WIN)
  return QApplication::applicationDirPath() + "/db";
#elif defined(Q_OS_MACOS)
  return QDir::cleanPath(QApplication::applicationDirPath() + "/../Resources");
#elif defined(Q_OS_LINUX)
  return QDir::cleanPath(QApplication::applicationDirPath() +
                         "/../share/olam/data/db");
#else
  return QApplication::applicationDirPath() + "/db";
#endif
}

static QString getOlamDbPath() {
  return getResourcePath() + "/olamdb.db";
}

static QString getDatukDbPath() {
  return getResourcePath() + "/datuk.sqlite";
}

bool Olam::createConnection() {
  QString olamPath = getOlamDbPath();
  QString datukPath = getDatukDbPath();
  qDebug() << "createConnection: olamdb =" << olamPath;
  qDebug() << "createConnection: datuk  =" << datukPath;

  if (!QFileInfo::exists(olamPath))
    qCritical() << "createConnection: olamdb file not found at" << olamPath;
  if (!QFileInfo::exists(datukPath))
    qCritical() << "createConnection: datuk file not found at" << datukPath;

  QSqlDatabase olam = QSqlDatabase::addDatabase("QSQLITE", "olam");
  olam.setDatabaseName(olamPath);
  QSqlDatabase datuk = QSqlDatabase::addDatabase("QSQLITE", "datuk");
  datuk.setDatabaseName(datukPath);

  bool olamOk = olam.open();
  bool datukOk = datuk.open();

  if (!olamOk)
    qCritical() << "createConnection: failed to open olamdb:" << olam.lastError().text();
  else
    qDebug() << "createConnection: olamdb opened successfully";

  if (!datukOk)
    qCritical() << "createConnection: failed to open datuk:" << datuk.lastError().text();
  else
    qDebug() << "createConnection: datuk opened successfully";

  if (!olamOk || !datukOk) {
    QMessageBox::critical(nullptr, "Connection to dictionary failed",
                          olam.lastError().text());
  }

  return olamOk && datukOk;
}

void Olam::handleLink(QUrl link) {
  QString raw = link.toString();
  qDebug() << "handleLink(QUrl): raw URL =" << raw;

  int sep = raw.indexOf(':');
  if (sep < 0) {
    qWarning() << "handleLink(QUrl): no ':' found in URL, ignoring";
    return;
  }
  QString action = raw.left(sep);
  QString word = raw.mid(sep + 1);
  qDebug() << "handleLink(QUrl): action =" << action << "word =" << word;

  if (action == "translate") {
    ui->dict_word->setText(word);
    ui->maleng_search->click();
  } else if (action == "speak") {
    qDebug() << "handleLink(QUrl): speaking word" << word;
    QTextToSpeech *tt = new QTextToSpeech(this);
    tt->setLocale(QLocale::Malayalam);
    tt->say(word);
  } else {
    qWarning() << "handleLink(QUrl): unknown action" << action;
  }
}

// eng-mal or mal-eng dictionary lookup
QString Olam::handleLink(QString word) {
  qDebug() << "handleLink(QString): looking up word =" << word;

  QSqlDatabase db = QSqlDatabase::database("olam");
  if (!db.isOpen()) {
    qWarning() << "handleLink(QString): db not open, attempting to reopen";
    if (!db.open()) {
      qCritical() << "handleLink(QString): failed to open db:" << db.lastError().text();
      return {};
    }
  }

  word = word.trimmed();
  if (word.isEmpty()) {
    qDebug() << "handleLink(QString): empty word, returning";
    return {};
  }

  word = word.left(1).toUpper() + word.mid(1);
  QString lang = OlamDatabase::detect_language(word);
  qDebug() << "handleLink(QString): detected lang =" << lang << "word =" << word;

  QString querystring;
  if (lang == "eng") {
    querystring = QString("SELECT malayalam, types FROM dictionary WHERE english = '%1'")
                      .arg(word);
  } else {
    querystring = QString("SELECT english, types FROM dictionary WHERE malayalam = '%1'")
                      .arg(word);
  }
  qDebug() << "handleLink(QString): query =" << querystring;

  QSqlQuery query(db);
  if (!query.exec(querystring)) {
    qCritical() << "handleLink(QString): query failed:" << query.lastError().text();
    return {};
  }

  QList<OlamWord> olamWords;
  while (query.next()) {
    olamWords.append(OlamWord(query.value(0).toString(), query.value(1).toString()));
  }
  qDebug() << "handleLink(QString): found" << olamWords.size() << "results";

  QList<OlamWord> noun, verb, adj, adverb, other;
  for (const OlamWord &w : olamWords) {
    if (w.pos == "n")        noun   << w;
    else if (w.pos == "v")   verb   << w;
    else if (w.pos == "a")   adj    << w;
    else if (w.pos == "adv") adverb << w;
    else                     other  << w;
  }

  QString result;
  result += printpos("Noun", noun);
  result += printpos("Verb", verb);
  result += printpos("Adverb", adverb);
  result += printpos("Adjective", adj);
  result += printpos("Other", other);

  if (result.isEmpty()) {
    result = "<li>No results found</li>";
  }
  return result;
}

void Olam::on_maleng_search_clicked() {
  qDebug() << "on_maleng_search_clicked";
  QString result = handleLink(ui->dict_word->text());
  if (result.isEmpty()) {
    result = "<li>The given word not found in the database</li>";
  }
  ui->dict_result->setText(result);
}

void Olam::on_malmal_search_clicked() {
  qDebug() << "on_malmal_search_clicked";
  QString result = searchcorpus(ui->corpus_word->text()).trimmed();
  ui->corpus_result->setText(result);
}

QString Olam::searchcorpus(QString word) {
  word = word.trimmed();
  qDebug() << "searchcorpus: word =" << word;

  QSqlDatabase db = QSqlDatabase::database("datuk");
  if (!db.isOpen()) {
    qWarning() << "searchcorpus: db not open, attempting to reopen";
    if (!db.open()) {
      qCritical() << "searchcorpus: failed to open datuk db:" << db.lastError().text();
      return "<li>Database unavailable</li>";
    }
  }

  QString querystring =
      QString("SELECT definition, rtype, letter FROM word, relation, definition "
              "WHERE word.id = relation.id_word "
              "AND relation.id_definition = definition.id "
              "AND word.word = '%1'")
          .arg(word);
  qDebug() << "searchcorpus: query =" << querystring;

  QSqlQuery query(db);
  if (!query.exec(querystring)) {
    qCritical() << "searchcorpus: query failed:" << query.lastError().text();
    return "<li>Query failed</li>";
  }

  QString result = "<ul>";
  while (query.next()) {
    result += "<li>" + query.value(0).toString()
            + " <b>" + query.value(1).toString() + "</b>"
            + "</li>";
  }
  result += "</ul>";

  if (result == "<ul></ul>") {
    result = "<li>No results found</li>";
  }
  return result;
}

QString Olam::printpos(QString pos, QList<OlamWord> wordlist) {
  if (wordlist.isEmpty())
    return {};
  QString out = "<h2>" + pos + "</h2><ul>";
  for (const OlamWord &w : wordlist) {
    out += w.toS();
  }
  out += "</ul>";
  return out;
}

void Olam::on_dict_word_textEdited(const QString &) {
  QString word = ui->dict_word->text().trimmed();
  OlamDatabase olamDatabase;
  QStringList wordList = olamDatabase.suggestions(word);
  QCompleter *completer = new QCompleter(wordList, this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->dict_word->setCompleter(completer);
}

void Olam::on_action_About_triggered() {
  About *dialog = new About();
  dialog->show();
}

void Olam::on_corpus_word_textEdited(const QString &) {
  QSqlDatabase db = QSqlDatabase::database("datuk");
  if (!db.isOpen() && !db.open()) {
    qWarning() << "on_corpus_word_textEdited: datuk db not available";
    return;
  }

  QString word = ui->corpus_word->text().trimmed();
  QString querystring = QString("SELECT DISTINCT word FROM word WHERE word LIKE '%1%' LIMIT 10")
                            .arg(word);

  QSqlQuery query(db);
  if (!query.exec(querystring)) {
    qWarning() << "on_corpus_word_textEdited: autocomplete query failed:" << query.lastError().text();
    return;
  }

  QStringList wordList;
  while (query.next()) {
    wordList << query.value(0).toString();
  }

  QCompleter *completer = new QCompleter(wordList, this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->corpus_word->setCompleter(completer);
}

void Olam::on_dict_word_returnPressed() {
  qDebug() << "on_dict_word_returnPressed";
  QString result = handleLink(ui->dict_word->text());
  if (result.isEmpty()) {
    result = "<li>The given word not found in the database</li>";
  }
  ui->dict_result->setText(result);
}

void Olam::on_action_Exit_triggered() { qApp->quit(); }

void Olam::on_corpus_word_returnPressed() {
  qDebug() << "on_corpus_word_returnPressed";
  QString result = searchcorpus(ui->corpus_word->text()).trimmed();
  ui->corpus_result->setText(result);
}
