#ifndef VIGENERENCODER_H
#define VIGENERENCODER_H

#include <QSet>
#include "iencoder.h"

class VigenerEncoder : public IEncoder
{
private:
    int currKeySym;

public:
    QString encode(QString dataStr) override;
    QString decode(QString dataStr) override;
    bool setKey(QString key) override;
    void prepareToCode() override;
    void resetCurrKeySym();
    QString getLastError() override;

    ~VigenerEncoder();
};

#endif // VIGENERENCODER_H
