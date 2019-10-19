#include "olamdatabase.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
using namespace std;


QString OlamDatabase::detect_language(QString word)
{
    QRegExp rx("[a-zA-Z]*");
    rx.setPatternSyntax(QRegExp::Wildcard);
    return rx.exactMatch(word) ? "eng" : "mal";
}

OlamDatabase::OlamDatabase()
{
    this->db = QSqlDatabase::database("olam");
}

QStringList OlamDatabase::suggestions(QString word)
{
    this->db.open();
    QSqlQuery query(this->db);
    word = word.trimmed();
    QString lang = detect_language(word);
    QString querystring, source_table;
    if(lang=="eng")
    {
        source_table = "english";
        word = word.left(1).toUpper() + word.mid(1); //capitalise first char
    }
    else if(lang=="mal")
    {
        source_table = "malayalam";
    }
    querystring = QString("SELECT DISTINCT %1 FROM olam WHERE %1 like '%2%' LIMIT 10").arg(source_table, word);
    qDebug() << querystring;
    query.exec(querystring);

    QStringList wordList;
    while (query.next()) {
        QString word = query.value(0).toString();
        wordList << word;
    }
    this->db.close();
    return wordList;
}
