#ifndef TEST_OLAM_DATABASE_TEST_H_
#define TEST_OLAM_DATABASE_TEST_H_

#include <QObject>
#include <QtTest>

#include "src/olamdatabase.h"

class OlamDatabaseTest : public QObject {
  Q_OBJECT

 private:
 private slots:
  void initTestCase() { qDebug("Init test"); }

  void suggestionsTest();

  void cleanupTestCase() { qDebug("Cleaning up"); }
};
// QTEST_MAIN(OlamDatabaseTest)

#endif  // TEST_OLAM_DATABASE_TEST_H_
