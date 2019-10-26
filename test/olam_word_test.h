#ifndef TEST_OLAM_WORD_TEST_H_
#define TEST_OLAM_WORD_TEST_H_

#include <QObject>
#include <QtTest>

#include "src/olamword.h"

class OlamWordTest : public QObject {
  Q_OBJECT

 private:
 private slots:
  void initTestCase() { qDebug("Init test"); }

  void formattingTest();

  void cleanupTestCase() { qDebug("Cleaning up"); }
};
// QTEST_MAIN(OlamWordTest)

#endif  // TEST_OLAM_WORD_TEST_H_
