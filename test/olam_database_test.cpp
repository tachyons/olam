#include "test/olam_database_test.h"

void OlamDatabaseTest::suggestionsTest() {
  OlamDatabase db = *new OlamDatabase;
  QStringList suggestions = {};
  QCOMPARE(db.suggestions("cat"), suggestions);
}
