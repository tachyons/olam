#include "olamword.h"

#include <QRegularExpression>

QString OlamWord::toS() const {
  return "<li>" + word + wordLink() + soundLink() + "</li>";
}

QString OlamWord::normalisedWord() const {
  QString nword = word;
  nword.replace(" ", "%20");
  return nword;
}

QString OlamWord::wordLink() const {
  return QString(" <a style='text-decoration:none;' href='translate:%1'>[&rarr;]</a>")
      .arg(normalisedWord());
}

QString OlamWord::soundLink() const {
  return QString(" <a style='text-decoration:none;' href='speak:%1'>[&#9654;]</a>")
      .arg(normalisedWord());
}
