#include "test/olam_database_test.h"

void OlamDatabaseTest::detect_language_data() {
    QTest::addColumn<QString>("word");
    QTest::addColumn<QString>("expected");

    // English: plain words, multi-word phrases, abbreviations with dots/hyphens
    QTest::newRow("english word")     << "Hello"          << "eng";
    QTest::newRow("english lower")    << "cat"            << "eng";
    QTest::newRow("english spaces")   << "A bed of roses" << "eng";
    QTest::newRow("english dots")     << "G.u.i"          << "eng";
    QTest::newRow("english hyphen")   << "Wi-Fi"          << "eng";
    QTest::newRow("english number")   << "catch22"        << "eng";

    // Malayalam: any non-ASCII character triggers "mal"
    QTest::newRow("malayalam")        << QString::fromUtf8("മലയാളം")     << "mal";
    QTest::newRow("mixed mal suffix") << QString::fromUtf8("hello മലയാളം") << "mal";
}

void OlamDatabaseTest::detect_language() {
    QFETCH(QString, word);
    QFETCH(QString, expected);
    QCOMPARE(OlamDatabase::detect_language(word), expected);
}

void OlamDatabaseTest::suggestions_no_crash() {
    // The live DB is not available in CI; verify suggestions() doesn't crash
    // and always returns a QStringList (possibly empty).
    OlamDatabase db;
    QStringList result = db.suggestions("cat");
    QVERIFY(result.size() >= 0);
}
