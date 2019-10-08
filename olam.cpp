#include "olam.h"
#include "ui_olam.h"
#include "about.h"
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
QString Olam::translate(QString text)
{
    QSqlDatabase db=QSqlDatabase::database("olam");
    db.open();
    QSqlQuery query(db);
    QString querystring,word;
    QStringList words;
    QStringList poss;
    QList<QPair<QString, QString> > entry;
    QList<QPair<QString, QString> >poslist;
    //get english word
    word=text;
    word=word.trimmed();
    //word=text;
    word= word.left(1).toUpper()+word.mid(1);//capitalise first char
    QString lang=detect_language(word);
    if(lang=="eng")
    {
        querystring="select malayalam  , pos from olam where english = \"";
    }
    else if(lang=="mal")
    {
        querystring="select english  , pos from olam where malayalam = \"";
    }
    querystring.append(word);
    querystring.append("\"");
    query.exec(querystring);
    //int i=0;
    while (query.next())
    {
        QPair<QString, QString> pair;
        pair.first =query.value(0).toString();
        pair.second=query.value(1).toString();
        entry.append(pair);
    }
    QString result="",po;
    QStringList noun,verb,adj,adverb,other;
    for (int i = 0; i < entry.size(); ++i)
    {
        po = entry.at(i).second;
        if(po=="n")
        {
            noun<<entry.at(i).first;
        }
        else if(po=="v")
        {
            verb<<entry.at(i).first;
        }
        else if(po=="a")
        {
            adj<<entry.at(i).first;
        }
        else if(po=="adv")
        {
            adverb<<entry.at(i).first;
        }
        else
        {
            other<<entry.at(i).first;
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
    querystring="select definition,rtype,letter from word,relation,definition where word.id = relation.id_word AND relation.id_definition = definition.id and word =\"";
    querystring.append(word);
    querystring.append("\"");
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
    db.close();
    return result;
    //return querystring;
}

QString Olam::printpos(QString pos,QStringList wordlist)
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
            returnstring+="<li>";
            returnstring+=wordlist.at(i);
            returnstring+="</li>";
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
    QSqlDatabase db=QSqlDatabase::database("olam");
    db.open();
    QSqlQuery query(db);
    QString tempword=ui->dict_word->text();
    tempword=tempword.trimmed();
    QString lang=detect_language(tempword);
    QString querystring;
    if(lang=="eng")
    {
        querystring="select DISTINCT english from olam where english like '";
        tempword= tempword.left(1).toUpper()+tempword.mid(1);//capitalise first char
    }
    else if(lang=="mal")
    {
        querystring="select DISTINCT malayalam from olam where malayalam like '";
    }

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
        QString word = query.value(0).toString();
        wordList <<word;
        //result.append("\n");
    }
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
        cout<<"not valid";
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
