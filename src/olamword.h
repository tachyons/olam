#ifndef OLAMWORD_H
#define OLAMWORD_H

#include <QString>

class OlamWord {
 public:
  QString word, pos;
  OlamWord(QString word, QString pos) {
    this->word = word;
    this->pos = pos;
  }

  QString toS() const { return "<li>" + word + "</li>"; }
};

#endif  // OLAMWORD_H
