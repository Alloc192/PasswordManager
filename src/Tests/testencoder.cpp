#include "testencoder.h"

TestEncoder::TestEncoder(QObject *parent) : QObject(parent)
{ }

//=============================================================================

void TestEncoder::setKey_data()
{
    QTest::addColumn<QString>("key");
    QTest::addColumn<bool>("result");

    QTest::newRow("Empty key") << "" << false;
    QTest::newRow("Short key") << "1234" << false;
    QTest::newRow("Simple key") << "12341234" << false;
    QTest::newRow("Valid key") << "12345678" << true;
}

//=============================================================================

void TestEncoder::setKey()
{
    IEncoder *encoder;
    encoder = new VigenerEncoder();

    QFETCH(QString, key);
    QFETCH(bool, result);
    QCOMPARE(encoder->setKey(key), result);
    delete encoder;
}

//=============================================================================

void TestEncoder::encodeDecode_data()
{
    QTest::addColumn<QString>("phrase");

    QTest::newRow("Alphabet") << "aBcDeFgHiJkLmNoPqRsTuVwXy";
    QTest::newRow("Numbers") << "0123456789";
    QTest::newRow("Special characters") << "!@#$%^&*()_+-=";
    QTest::newRow("With space") << "Simple phrase";
}

//=============================================================================

void TestEncoder::encodeDecode()
{
    QStringList keys;
    keys << "password" << "12345678" << "key_12_!@#$%^&*()_+-=";

    IEncoder *encoder;
    encoder = new VigenerEncoder();
    for(QString key : qAsConst(keys))
    {
        encoder->setKey(key);
        QFETCH(QString, phrase);
        QString encodedPhrase;
        encodedPhrase = encoder->encode(phrase);
        QString decodedPhrase;
        encoder->prepareToCode();
        decodedPhrase = encoder->decode(encodedPhrase);
        QCOMPARE(decodedPhrase, phrase);
    }
    delete encoder;
}
