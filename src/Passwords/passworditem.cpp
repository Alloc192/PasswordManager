#include "passworditem.h"

PasswordItem::PasswordItem(IEncoder *encoder,
        QStandardItem *parent,
        QJsonObject object)
{
    if(
            (!object.contains("login")) ||
            (!object.contains("password"))
    )
    {
        throw 0;
    }
    QString loginData;
    loginData = object["login"].toString();
    loginData = encoder->decode(loginData);

    QString passwData;
    passwData = object["password"].toString().toUtf8();
    passwData = encoder->decode(passwData);

    this->setText(loginData);
    passItem = new QStandardItem();
    passItem->setText(passwData);
    int row = parent->rowCount();
    parent->setChild(row, 0, this);
    parent->setChild(row, 1, passItem);
}

//=============================================================================

PasswordItem::PasswordItem(QStandardItem *parent)
{
    this->setText("New login");
    QString newPassword;
    newPassword = PasswordGenerator::generate();

    passItem = new QStandardItem(newPassword);

    int row = parent->rowCount();
    parent->setChild(row, 0, this);
    parent->setChild(row, 1, passItem);
}

//=============================================================================

QJsonObject PasswordItem::toJsonObject(IEncoder *encoder)
{
    QJsonObject output;
    QString loginData;
    loginData = this->text();
    loginData = encoder->encode(loginData);

    QString passwData;
    passwData = passItem->text();
    passwData = encoder->encode(passwData);

    output.insert("login", loginData);
    output.insert("password", passwData);
    return output;
}
