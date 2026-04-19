#pragma once

#include <QObject>
#include <QtTest>

#include "src/olamdatabase.h"

class OlamDatabaseTest : public QObject {
    Q_OBJECT

private slots:
    // detect_language — pure function, no DB needed
    void detect_language_data();
    void detect_language();

    // suggestions — needs DB; verified to not crash; may return empty in CI
    void suggestions_no_crash();
};
