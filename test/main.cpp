#include <QCoreApplication>
#include <QTest>

#include "test/olam_database_test.h"
#include "test/olam_word_test.h"

// Run all test objects in a single binary.
// QCoreApplication is required for QSqlDatabase.
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    int status = 0;
    status |= QTest::qExec(new OlamWordTest,     argc, argv);
    status |= QTest::qExec(new OlamDatabaseTest, argc, argv);
    return status;
}
