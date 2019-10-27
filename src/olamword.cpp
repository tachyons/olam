#include "olamword.h"

#include <QRegExp>

QString OlamWord::toS() const {
  QString normalizedWord = word;
  normalizedWord.replace(" ", "%20");

  return "<li>" + word + wordLink() + soundLink() + "</li>";
}
QString OlamWord::normalisedWord() const {
  QString nword = word;
  nword.replace(" ", "%20");
  return nword;
}
QString OlamWord::wordLink() const {
  return QString("<a style= 'text-decoration: none;' href=translate:%1>🔎</a>")
    .arg(normalisedWord());
}
QString OlamWord::soundLink() const {
  return QString("<a style= 'text-decoration: none;' href=speak:%1>🗣<a>")
    .arg(normalisedWord());
 }
