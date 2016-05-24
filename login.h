#pragma once

#include <QtWidgets>
#include "mainwindow.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

signals:
    void sendLoginInfo(QString name, int group);

private slots:
    void pushButton_login_clicked();

public slots:
    void showLoginWindow();

private:
    int group = 0;
    QString realname;
    MainWindow *mainForm;
    Ui::Login *ui;

    QWidget *w;
    QLabel *imgLabel;
    QLabel *loginLabel;
    QLabel *passLabel;
    QLineEdit *lineEdit_username;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_login;

};

