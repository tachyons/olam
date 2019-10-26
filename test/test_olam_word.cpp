#include <QObject>
#include <QtTest>

#include "src/olamword.h"

class OlamWordTest : public QObject {
  Q_OBJECT

 private:
  bool myCondition() { return true; }

 private slots:
  void initTestCase() { qDebug("Init test"); }

  void formattingTest() {
    OlamWord word = *new OlamWord("word", "poc");
    QCOMPARE(word.toS(), "<li>word</li>");
  }

  void cleanupTestCase() { qDebug("Cleaning up"); }
};
// QTEST_MAIN(OlamWordTest)
#include "test_olam_word.moc"
