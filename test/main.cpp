#include <QTest>
#include <QtTest/QtTest>

#include "test_olam_database.cpp"
#include "test_olam_word.cpp"

int main(int argc, char *argv[]) {
  int status = 0;
  status |= QTest::qExec(new OlamWordTest, argc, argv);
  status |= QTest::qExec(new OlamDatabaseTest, argc, argv);
  return status;
}
