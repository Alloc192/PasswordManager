#ifndef PASSWORDLISTCONTROLLER_H
#define PASSWORDLISTCONTROLLER_H

#include <QStandardItemModel>
#include <QTreeView>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "Encoder/vigenerencoder.h"
#include "Passwords/accountitem.h"
#include "Passwords/passworditem.h"

enum ControllerStates
{
    NO_ERROR = 0,
    WARNING = 1,
    ERROR = 2
};

class PasswordListController
{
private:
    IEncoder *encoder;
    QStandardItemModel *model;
    QTreeView *treeView;
    QString lastError;

public:
    PasswordListController(IEncoder *encoder, QTreeView *treeView);
    ControllerStates prepareModel();
    QString getLastError();
    void addNewItem(bool account);
    void removeItem();
    ControllerStates saveModelToJson();
};

#endif // PASSWORDLISTCONTROLLER_H
