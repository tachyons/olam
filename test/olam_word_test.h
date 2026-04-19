#pragma once

#include <QObject>
#include <QtTest>

#include "src/olamword.h"

class OlamWordTest : public QObject {
    Q_OBJECT

private slots:
    void normalise_plain();
    void normalise_spaces();
    void toS_structure();
    void toS_exact();
    void toS_with_spaces();
};
