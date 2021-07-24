#ifndef TESTENCODER_H
#define TESTENCODER_H

#include <QObject>
#include <QtTest>

#include "Encoder/vigenerencoder.h"

class TestEncoder : public QObject
{
    Q_OBJECT
public:
    explicit TestEncoder(QObject *parent = nullptr);



private slots:
    void setKey_data();
    void setKey();
    void encodeDecode_data();
    void encodeDecode();

};

#endif // TESTENCODER_H
