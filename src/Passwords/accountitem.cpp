#include "accountitem.h"

AccountItem::AccountItem(IEncoder *encoder, QJsonObject object)
{
    if(
            (!object.contains("name")) ||
            (!object.contains("passwords"))
    )
    {
        throw 0;
    }
    QString name;
    name = object["name"].toString();
    name = encoder->decode(name);
    this->setText(name);
    QJsonArray passwArray;
    passwArray = object["passwords"].toArray();
    for(auto password : qAsConst(passwArray))
    {
        PasswordItem *item;
        item = new PasswordItem(encoder, this, password.toObject());
    }
}

//=============================================================================

AccountItem::AccountItem()
{
    this->setText("New account");
}

//=============================================================================

QJsonObject AccountItem::toJsonObject(IEncoder *encoder)
{
    QJsonObject output;
    QString name;
    name = encoder->encode(this->text());
    output.insert("name", name);
    QJsonArray passwArray;
    for(int i = 0; i < rowCount(); i++)
    {
        PasswordItem *item;
        item = dynamic_cast<PasswordItem*>(this->child(i, 0));
        passwArray.append(item->toJsonObject(encoder));
    }
    output.insert("passwords", passwArray);
    return output;
}
