#ifndef OLAM_H
#define OLAM_H

#include <QMainWindow>
#include <QUrl>

#include "olamword.h"

namespace Ui {
class Olam;
}

class Olam : public QMainWindow {
  Q_OBJECT

 public:
  explicit Olam(QWidget *parent = nullptr);
  ~Olam();

  void setupTrayIcon();

 private slots:
  bool createConnection();
  QString handleLink(QString text);
  void handleLink(QUrl word);

  void on_maleng_search_clicked();
  void on_malmal_search_clicked();
  QString printpos(QString pos, QList<OlamWord> wordlist);

  void on_dict_word_textEdited(const QString &arg1);
  void on_action_About_triggered();
  QString searchcorpus(QString word);

  void on_corpus_word_textEdited(const QString &arg1);
  void on_dict_word_returnPressed();
  void on_action_Exit_triggered();
  void on_corpus_word_returnPressed();
  void openHelpUrl();

 private:
  Ui::Olam *ui;
};

#endif  // OLAM_H
