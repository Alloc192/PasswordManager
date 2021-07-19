#ifndef PASSWORDWINDOW_H
#define PASSWORDWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "ui_passwordwindow.h"

#include "Passwords/passwordlistcontroller.h"

namespace Ui {
class PasswordWindow;
}

class PasswordWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PasswordWindow(IEncoder *encoder, QWidget *parent = nullptr);
    ~PasswordWindow();

private slots:
    void on_addElement_clicked();
    void on_removeElement_clicked();
    void on_saveModel_clicked();

private:
    Ui::PasswordWindow *ui;
    IEncoder *encoder;
    PasswordListController *passwordCtr;
};

#endif // PASSWORDWINDOW_H
