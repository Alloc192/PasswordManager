#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("Password manager");

    encoder = new VigenerEncoder;
    ui->pushButton->setShortcut(Qt::Key_Return);
}

//=============================================================================

MainWindow::~MainWindow()
{
    delete encoder;
    delete ui;
}

//=============================================================================

void MainWindow::on_pushButton_clicked()
{
    QString password;
    password = ui->lineEdit->text();

    if(!encoder->setKey(password))
    {
        QMessageBox::critical(this, "Error!", encoder->getLastError());
        ui->lineEdit->clear();
        return;
    }

    PasswordWindow* passWindow;
    passWindow = new PasswordWindow(encoder, this);
}
