#include "test/olam_word_test.h"

void OlamWordTest::formattingTest() {
  OlamWord word = *new OlamWord("word", "poc");
  QCOMPARE(word.toS(), QString("<li>word</li>"));
}
