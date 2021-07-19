#ifndef ACCOUNTITEM_H
#define ACCOUNTITEM_H

#include <QStandardItem>
#include <QJsonObject>
#include <QJsonArray>

#include "Encoder/vigenerencoder.h"
#include "Passwords/passworditem.h"

class AccountItem : public QStandardItem
{
public:
    AccountItem(IEncoder *encoder, QJsonObject object);
    AccountItem();
    QJsonObject toJsonObject(IEncoder *encoder);
};

#endif // ACCOUNTITEM_H
