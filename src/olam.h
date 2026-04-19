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
  // Auto-connected UI slots
  void on_maleng_search_clicked();
  void on_malmal_search_clicked();
  void on_copy_dict_clicked();
  void on_copy_corpus_clicked();
  void on_action_DarkMode_triggered();
  void on_dict_word_textEdited(const QString &);
  void on_corpus_word_textEdited(const QString &);
  void on_dict_word_returnPressed();
  void on_corpus_word_returnPressed();
  void on_action_About_triggered();
  void on_action_Exit_triggered();

  // Signal-connected slots
  void handleLink(QUrl url);
  void openHelpUrl();
  bool createConnection();

 private:
  Ui::Olam *ui;
  bool m_isDark = false;

  // Theme
  void applyTheme(bool dark);
  void updateResultStylesheets();

  // Features
  void showWordOfTheDay();
  void addToHistory(const QString &word);

  // Helpers
  QString lookupWord(const QString &word);
  QString searchcorpus(const QString &word);
  QString printpos(const QString &pos, const QList<OlamWord> &wordlist);
};

#endif  // OLAM_H
