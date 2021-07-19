#include "passwordlistcontroller.h"

PasswordListController::PasswordListController(
        IEncoder *encoder,
        QTreeView *treeView)
{
    this->encoder = encoder;
    this->treeView = treeView;
    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList() << "Login" << "Password");
    treeView->setModel(model);
    treeView->setColumnWidth(0, 200);
    treeView->setAlternatingRowColors(true);
}

//=============================================================================

ControllerStates PasswordListController::prepareModel()
{
    lastError.clear();
    QFile checkPasswords("passwords.json");
    if(!checkPasswords.exists())
    {
        lastError =  "File with passwords not found. "
            "A new password file will be created.\n"
            "If this is the first launch of the program, "
            "do not pay attention to this warning.";
        return ControllerStates::WARNING;
    }
    QFile savefile("passwords.json");
    if(!savefile.open(QIODevice::ReadWrite))
    {
        lastError = "Fatal error while trying to open passwords file.";
        return ControllerStates::ERROR;
    }
    QJsonDocument doc;
    QJsonParseError docErr;
    doc = QJsonDocument::fromJson(savefile.readAll(), &docErr);
    savefile.close();
    if(docErr.errorString().toInt() != QJsonParseError::NoError)
    {
        lastError = "Fatal error while parsing passwords file.\n" +
            docErr.errorString();
        return ControllerStates::ERROR;
    }
    QJsonObject rootObj;
    rootObj = doc.object();
    if(!rootObj.contains("accounts"))
    {
        lastError = "File with passwords is empty or has invalid format.\n"
            "If this is the first launch of the program, "
            "do not pay attention to this warning.";
        return ControllerStates::WARNING;
    }
    if(!rootObj["accounts"].isArray())
    {
        lastError = "File with passwords has invalid format.\n"
            "If this is the first launch of the program, "
            "do not pay attention to this warning.";
        return ControllerStates::WARNING;
    }
    QJsonArray accountsArr = rootObj["accounts"].toArray();
    if(accountsArr.isEmpty())
    {
        lastError = "Password list is empty.\n"
            "If this is the first launch of the program, "
            "do not pay attention to this warning.";
        return ControllerStates::WARNING;
    }
    QStandardItem *root;
    root = model->invisibleRootItem();


    try {
        for(auto accaunt : qAsConst(accountsArr))
        {
            AccountItem *item;
            item = new AccountItem(encoder, accaunt.toObject());
            root->setChild(root->rowCount(), item);
        }
    }
    catch (int)
    {
        lastError = "Fatal error while parsing passwords file.\n" +
            docErr.errorString();
        return ControllerStates::ERROR;
    }

    treeView->setColumnWidth(0, 200);
    return ControllerStates::NO_ERROR;
}

//=============================================================================

QString PasswordListController::getLastError()
{
    return lastError;
}

//=============================================================================

void PasswordListController::addNewItem(bool account)
{

    if(account)
    {
        QStandardItem *root;
        root = model->invisibleRootItem();
        root->setChild(root->rowCount(), new AccountItem());
    }
    else
    {
        QModelIndex index = treeView->currentIndex();
        if(index.parent().isValid())
        {
            index = index.parent();
        }
        if(index.isValid())
        {
            QStandardItem *item;
            item = model->itemFromIndex(index);
            PasswordItem *newItem;
            newItem = new PasswordItem(item);
            treeView->expand(index);
        }
    }
}

//=============================================================================

void PasswordListController::removeItem()
{
    QModelIndex index = treeView->currentIndex();
    model->removeRow(index.row(), index.parent());
}

//=============================================================================

ControllerStates PasswordListController::saveModelToJson()
{
    QFile savefile("passwords.json");
    if(!savefile.open(QIODevice::WriteOnly))
    {
        lastError = "Fatal error while trying to open passwords file.";
        return ControllerStates::ERROR;
    }
    QJsonDocument doc;
    QJsonObject accounts;
    QJsonArray accountsArr;
    QStandardItem *root;
    encoder->prepareToCode();
    root = model->invisibleRootItem();
    for(int i = 0; i < root->rowCount(); i++)
    {
        AccountItem *item;
        item = dynamic_cast<AccountItem*>(root->child(i, 0));
        accountsArr.append(item->toJsonObject(encoder));
    }
    accounts.insert("accounts", accountsArr);
    doc.setObject(accounts);
    qDebug() << doc.toJson();
    savefile.write(doc.toJson());
    savefile.close();
    return ControllerStates::NO_ERROR;
}
