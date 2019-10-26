#ifndef OLAMDATABASE_H
#define OLAMDATABASE_H

#include <QSqlDatabase>

class OlamDatabase {
 private:
  QSqlDatabase db;
  QString detect_language(QString word);

 public:
  OlamDatabase();
  QStringList suggestions(QString word);
};

#endif  // OLAMDATABASE_H
