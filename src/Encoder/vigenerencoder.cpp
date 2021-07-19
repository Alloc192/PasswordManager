#include "vigenerencoder.h"

#include <QDebug>


//=============================================================================

bool VigenerEncoder::setKey(QString key)
{
    key.replace(' ',"");
    if(key.isEmpty())
    {
        lastError.clear();
        lastError = "Password cannot be empty.";
        return false;
    }

    if(key.length() < 8)
    {
        lastError.clear();
        lastError = "Password must not be shorter than 8 characters.";
        return false;
    }

    QSet<QChar> charset;
    for(QChar ch : key)
    {
        charset.insert(ch);
    }
    if (charset.size() < 5)
    {
        lastError.clear();
        lastError = "Password must contain at least 5 different characters.";
        return false;
    }

    this->key = key;
    prepareToCode();    return true;
}

//=============================================================================

QString VigenerEncoder::encode(QString dataStr)
{
    QString output = "";
    for(QChar ch : dataStr)
    {
        QChar newCh(ch.unicode() + key.at(currKeySym).unicode());
        output.append(newCh);
        currKeySym = (currKeySym + 1) % key.size();
    }
    return output;
}

//=============================================================================

QString VigenerEncoder::decode(QString dataStr)
{
    QString output = "";
    for(QChar ch : dataStr)
    {
        QChar newCh(ch.unicode() - key.at(currKeySym).unicode());
        output.append(newCh);
        currKeySym = (currKeySym + 1) % key.size();
    }
    return output;
}

//=============================================================================

void VigenerEncoder::prepareToCode()
{
    currKeySym = 0;
}

//=============================================================================

QString VigenerEncoder::getLastError()
{
    return lastError;
}

//=============================================================================

VigenerEncoder::~VigenerEncoder()
{

}
