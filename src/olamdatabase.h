#ifndef OLAMDATABASE_H
#define OLAMDATABASE_H

#include <QStringList>

class OlamDatabase {
public:
    QStringList suggestions(QString word);
    static QString detect_language(const QString &word);
};

#endif  // OLAMDATABASE_H
