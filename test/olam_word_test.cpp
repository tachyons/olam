#include "test/olam_word_test.h"

// normalisedWord() is private; test it indirectly via toS() link hrefs.

void OlamWordTest::normalise_plain() {
    // A plain word should appear as-is in the href.
    OlamWord w("hello", "n");
    QVERIFY(w.toS().contains("href='translate:hello'"));
}

void OlamWordTest::normalise_spaces() {
    // Spaces must be percent-encoded so the href is a valid token.
    OlamWord w("A bed of roses", "n");
    QVERIFY(w.toS().contains("href='translate:A%20bed%20of%20roses'"));
}

void OlamWordTest::toS_structure() {
    OlamWord w("word", "n");
    const QString s = w.toS();
    QVERIFY2(s.startsWith("<li>"),    "must open with <li>");
    QVERIFY2(s.endsWith("</li>"),     "must close with </li>");
    QVERIFY2(s.contains("href='translate:word'"), "translate link");
    QVERIFY2(s.contains("href='speak:word'"),     "speak link");
    QVERIFY2(s.contains("[&rarr;]"),  "arrow entity for translate");
    QVERIFY2(s.contains("[&#9654;]"), "play entity for speak");
}

void OlamWordTest::toS_exact() {
    OlamWord w("word", "poc");
    QCOMPARE(w.toS(),
             QString("<li>word"
                     " <a style='text-decoration:none;' href='translate:word'>[&rarr;]</a>"
                     " <a style='text-decoration:none;' href='speak:word'>[&#9654;]</a>"
                     "</li>"));
}

void OlamWordTest::toS_with_spaces() {
    OlamWord w("A bed of roses", "n");
    const QString s = w.toS();
    QVERIFY(s.contains("href='translate:A%20bed%20of%20roses'"));
    QVERIFY(s.contains("href='speak:A%20bed%20of%20roses'"));
}
