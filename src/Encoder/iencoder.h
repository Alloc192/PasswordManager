#ifndef IENCODER_H
#define IENCODER_H

#include <QByteArray>
#include <QString>

class IEncoder
{
protected:
    QString key;
    QString lastError;

public:
    virtual QString encode(QString dataStr) = 0;
    virtual QString decode(QString dataStr) = 0;
    virtual void prepareToCode() = 0;
    virtual bool setKey(QString key) = 0;
    virtual QString getLastError() = 0;
    virtual ~IEncoder() {}
};

#endif // IENCODER_H
