#include "olamdatabase.h"

#include <QDebug>
#include <QRegularExpression>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

QString OlamDatabase::detect_language(const QString &word)
{
    QRegularExpression re("^[a-zA-Z ]+$");
    return re.match(word).hasMatch() ? "eng" : "mal";
}

QStringList OlamDatabase::suggestions(QString word)
{
    QSqlDatabase db = QSqlDatabase::database("olam");
    if (!db.isOpen()) db.open();

    word = word.trimmed();
    QString lang = detect_language(word);
    QString source_table;

    if (lang == "eng") {
        source_table = "english";
        word = word.left(1).toUpper() + word.mid(1);
    } else {
        source_table = "malayalam";
    }

    QString querystring = QString("SELECT DISTINCT %1 FROM dictionary WHERE %1 LIKE '%2%' LIMIT 10")
                              .arg(source_table, word);

    qDebug() << "OlamDatabase::suggestions: query =" << querystring;
    QSqlQuery query(db);
    if (!query.exec(querystring)) {
        qCritical() << "OlamDatabase::suggestions: query failed:" << query.lastError().text();
        return {};
    }

    QStringList wordList;
    while (query.next()) {
        wordList << query.value(0).toString();
    }
    qDebug() << "OlamDatabase::suggestions: found" << wordList.size() << "suggestions";
    return wordList;
}
