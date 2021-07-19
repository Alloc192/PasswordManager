#ifndef PASSWORDITEM_H
#define PASSWORDITEM_H

#include <QStandardItem>
#include <QJsonObject>

#include "Encoder/vigenerencoder.h"
#include "Passwords/passwordgenerator.h"

class PasswordItem : public QStandardItem
{
private:
    QStandardItem *passItem;

public:
    PasswordItem(IEncoder *encoder,
                 QStandardItem *parent,
                 QJsonObject object);

    PasswordItem(QStandardItem *parent);
    QJsonObject toJsonObject(IEncoder *encoder);
};

#endif // PASSWORDITEM_H
