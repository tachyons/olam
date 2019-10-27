#include "test/olam_word_test.h"

void OlamWordTest::formattingTest() {
  OlamWord word = *new OlamWord("word", "poc");
  QCOMPARE(word.toS(),
           QString("<li>word<a style= 'text-decoration: none;' "
                   "href=translate:word>🔎</a><a style= 'text-decoration: n"
                   "one;' href=speak:word>🗣<a></li>"));
}
