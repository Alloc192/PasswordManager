#include "passwordwindow.h"

PasswordWindow::PasswordWindow(IEncoder *encoder, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PasswordWindow)
{
    ui->setupUi(this);
    this->show();
    parent->hide();
    this->setWindowTitle("Password manager");

    this->encoder = encoder;
    passwordCtr = new PasswordListController(encoder, ui->treeView);
    ControllerStates state;
    state = passwordCtr->prepareModel();
    if(state == ControllerStates::ERROR)
    {
        QMessageBox::critical(this, "Error!", passwordCtr->getLastError());
    }
    if(state == ControllerStates::WARNING)
    {
        QMessageBox::warning(this, "Warning!", passwordCtr->getLastError());
    }
    ui->addElement->setShortcut(Qt::CTRL + Qt::Key_N);
    ui->removeElement->setShortcut(Qt::Key_Delete);
    ui->saveModel->setShortcut(Qt::CTRL + Qt::Key_S);
}

//=============================================================================

void PasswordWindow::on_addElement_clicked()
{
    QMessageBox msgBox(this);
    msgBox.setText(tr("Add new account or password?"));
    QAbstractButton* accountBtn;
    accountBtn = msgBox.addButton(tr("Account"), QMessageBox::NoRole);
    msgBox.addButton(tr("Password"), QMessageBox::NoRole);
    QAbstractButton* cancelBtn;
    cancelBtn = msgBox.addButton(tr("Cancel"), QMessageBox::RejectRole);
    msgBox.exec();
    if(msgBox.clickedButton() != cancelBtn)
    {
        passwordCtr->addNewItem(msgBox.clickedButton() == accountBtn);
    }
}

//=============================================================================

void PasswordWindow::on_removeElement_clicked()
{
    QMessageBox::StandardButton result;

    result = QMessageBox::question(this, "Confirm",
                "Are you sure you want to delete selected item?");
    if(result == QMessageBox::Yes)
    {
        passwordCtr->removeItem();
    }
}

//=============================================================================

void PasswordWindow::on_saveModel_clicked()
{
    QMessageBox::StandardButton result;

    result = QMessageBox::question(this, "Confirm",
                "Are you sure you want to save changes?");
    if(result == QMessageBox::Yes)
    {
        ControllerStates state;
        state = passwordCtr->saveModelToJson();
        if(state == ControllerStates::ERROR)
        {
            QMessageBox::critical(this, "Error!", passwordCtr->getLastError());
        }
        if(state == ControllerStates::WARNING)
        {
            QMessageBox::warning(this, "Warning!", passwordCtr->getLastError());
        }
    }

}

//=============================================================================

PasswordWindow::~PasswordWindow()
{
    delete ui;
}


