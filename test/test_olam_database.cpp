#include <QObject>
#include <QtTest>

#include "src/olamdatabase.h"

class OlamDatabaseTest : public QObject {
  Q_OBJECT

 private:
  bool myCondition() { return true; }

 private slots:
  void initTestCase() { qDebug("Init test"); }

  void suggestionsTest() {
    OlamDatabase db = *new OlamDatabase;
    QStringList suggestions = {};
    QCOMPARE(db.suggestions("cat"), suggestions);
  }

  void cleanupTestCase() { qDebug("Cleaning up"); }
};
// QTEST_MAIN(OlamDatabaseTest)
#include "test_olam_database.moc"
