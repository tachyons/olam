#include "olam.h"
#include "ui_olam.h"
#include "about.h"
#include "olamword.h"
#include "olamdatabase.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QCompleter>
#include <QSqlQuery>
#include <QMessageBox>
#include <iostream>
#include <QDir>
using namespace std;
Olam::Olam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Olam)
{
    ui->setupUi(this);
    createConnection();
    ui->dict_result->setFontPointSize(100);
    QFont font;
    font.setPixelSize(20);
    ui->dict_result->setFont(font);
}

Olam::~Olam()
{
    delete ui;
}

bool fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    return (check_file.exists() && check_file.isFile());
}

QString getResourcePath() {
  if(QDir("db").exists()) {
    return "./db";
  }
#if defined(Q_OS_WIN)
    return QApplication::applicationDirPath() + "/db";
#elif defined(Q_OS_OSX)
    return QApplication::applicationDirPath() + "/../Resources/";
#elif defined(Q_OS_LINUX)
    return QDir::cleanPath(QApplication::applicationDirPath() +  "/../share/olam/data/db");
#else
    return QApplication::applicationDirPath() + "/db";
#endif
}

QString getOlamDbPath(){
  qDebug() << getResourcePath();
   return getResourcePath() + "/olamdb.db";
}
QString getDatukDbPath(){
    return getResourcePath() + "/datuk.sqlite";
}

//create connection with db
bool Olam::createConnection()
{
    QSqlDatabase olam = QSqlDatabase::addDatabase("QSQLITE","olam");
    olam.setDatabaseName(getOlamDbPath());
    QSqlDatabase datuk = QSqlDatabase::addDatabase("QSQLITE","datuk");
    datuk.setDatabaseName(getDatukDbPath());

    if (!olam.open() || !datuk.open())
    {
        QMessageBox::information(nullptr, "Connection to dictionary Failed!", olam.lastError().text(),QMessageBox::Ok, QMessageBox::NoButton);
    }

    return true;

}

//eng-mal or mal-eng
QString Olam::translate(QString word)
{
    QSqlDatabase db=QSqlDatabase::database("olam");
    db.open();
    QSqlQuery query(db);
    QString querystring;
    QList<OlamWord> olamWords;
    word=word.trimmed();
    word= word.left(1).toUpper()+word.mid(1);//capitalise first char
    QString lang=detect_language(word);
    if(lang=="eng")
    {
        querystring=QString("SELECT malayalam, pos from olam where english = '%1'").arg(word);
    }
    else if(lang=="mal")
    {
        querystring=QString("SELECT english  , pos from olam where malayalam = '%1'").arg(word);
    }
    query.exec(querystring);
    while (query.next())
    {

        OlamWord word = *new OlamWord(query.value(0).toString(), query.value(1).toString());
        olamWords.append(word);
    }
    QString result="",po;
    QList<OlamWord> noun,verb,adj,adverb,other;
    for (int i = 0; i < olamWords.size(); ++i)
    {
        po = olamWords.at(i).pos;
        if(po=="n")
        {
            noun<<olamWords.at(i);
        }
        else if(po=="v")
        {
            verb<<olamWords.at(i);
        }
        else if(po=="a")
        {
            adj<<olamWords.at(i);
        }
        else if(po=="adv")
        {
            adverb<<olamWords.at(i);
        }
        else
        {
            other<<olamWords.at(i);
        }
    }
    QString pos;
    QStringList wordlist;
    result+=printpos("Noun",noun);
    result+=printpos("Verb",verb);
    result+=printpos("Adverb",adverb);
    result+=printpos("Adjective",adj);
    result+=printpos("Other",other);
    if(result.isEmpty())
    {
        result ="<li>No results found</li>";
    }
    return result;
}

void Olam::on_maleng_search_clicked()
{
    QString result= translate(ui->dict_word->text());
    if(result.isEmpty())
    {
        result ="<li>The given word not found in the database</li>";
    }
    ui->dict_result->setText(result);
}

void Olam::on_malmal_search_clicked()
{
    QString result;
    result=searchcorpus(ui->corpus_word->text());
    result=result.trimmed();
    ui->corpus_result->setText(result);
}

QString Olam::searchcorpus(QString word)
{
    QSqlDatabase db=QSqlDatabase::database("datuk");
    db.open();
    QSqlQuery query(db);
    QString querystring,result;
    QStringList deflist;
    word=word.trimmed();
    querystring=QString("select definition,rtype,letter from word,relation,definition where word.id = relation.id_word AND relation.id_definition = definition.id and word ='%1'").arg(word);
    if(!query.exec(querystring))
    {
        QMessageBox::critical(nullptr, qApp->tr("Cannot open database"),
                              qApp->tr("queryfailed."), QMessageBox::Cancel);
    }
    result+="<ul>";
    while (query.next())
    {
        result+="<li>";
        result+=query.value(0).toString();
        result+="<b>";
        result+=query.value(1).toString();
        result+="</b>";
        result+="</li>";
    }
    result+="</ul>";
    if(result.isEmpty())
    {
        result ="<li>No results found</li>";
    }
    db.close();
    return result;
    //return querystring;
}

QString Olam::printpos(QString pos, QList<OlamWord> wordlist)
{
    QString returnstring;
    if(wordlist.size()!=0)
    {
        returnstring+="<h2>";
        returnstring+=pos;
        returnstring+="</h2>";
        returnstring+="<ul>";
        for(int i=0;i<wordlist.size();i++)
        {
            returnstring+=wordlist.at(i).toS();
        }
        returnstring+="</ul>";
    }
    return returnstring;
}

QString Olam::detect_language(QString text)
{
    //need to implement better language detector
    QRegExp rx("[a-zA-Z]*");
    rx.setPatternSyntax(QRegExp::Wildcard);
    if(rx.exactMatch(text))
    {
        return "eng";
    }
    else
    {
        return "mal";
    }
}

void Olam::on_dict_word_textEdited(const QString &arg1)
{
    QString word = ui->dict_word->text().trimmed();
    OlamDatabase olamDatabase = *new OlamDatabase();
    QStringList wordList = olamDatabase.suggestions(word);
    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->dict_word->setCompleter(completer);
}

void Olam::on_action_About_triggered()
{
    About *dialog = new About();
    dialog->show();
}

void Olam::on_corpus_word_textEdited(const QString &arg1)
{
    QSqlDatabase db=QSqlDatabase::database("datuk");
    db.open();
    if(!db.isValid())
    {
        qDebug() <<"not valid";
    }
    QSqlQuery query(db);
    QString tempword=ui->corpus_word->text();
    tempword=tempword.trimmed();
    QString querystring="select DISTINCT word from word where word like '";
    //tempword= tempword.left(1).toUpper()+tempword.mid(1);//capitalise first char
    querystring+=tempword;
    querystring.append("%'");
    querystring.append(" limit 10");
    if(!query.exec(querystring))
    {
        QMessageBox::critical(nullptr, qApp->tr("Cannot open database"),
                              qApp->tr("queryfailed."), QMessageBox::Cancel);
    }
    QStringList wordList;
    while (query.next()) {
        QString word=query.value(0).toString();
        wordList <<word;
        //result.append("\n");
    }
    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->corpus_word->setCompleter(completer);
    db.close();
}

void Olam::on_dict_word_returnPressed()
{
    QString result= translate(ui->dict_word->text());
    if(result.isEmpty())
    {
        result ="<li>The given word not found in the database</li>";
    }
    ui->dict_result->setText(result);
}

void Olam::on_action_Exit_triggered()
{
    qApp->quit();
}

void Olam::on_corpus_word_returnPressed()
{

}
