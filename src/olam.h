#ifndef OLAM_H
#define OLAM_H

#include "olamword.cpp"

#include <QMainWindow>
#include <QRegExp>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class Olam;
}

class Olam : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Olam(QWidget *parent = nullptr);
    ~Olam();
    
private slots:

    bool createConnection();
    QString translate(QString text);

    void on_maleng_search_clicked();

    void on_malmal_search_clicked();
    QString detect_language(QString);
    QString printpos(QString pos,QList<OlamWord> wordlist);

    void on_dict_word_textEdited(const QString &arg1);

    void on_action_About_triggered();
    QString searchcorpus(QString word);

    void on_corpus_word_textEdited(const QString &arg1);

    void on_dict_word_returnPressed();

    void on_action_Exit_triggered();

    void on_corpus_word_returnPressed();

private:
    Ui::Olam *ui;
};

#endif // OLAM_H
