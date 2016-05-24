#pragma once

#include <QtWidgets>
#include <QtSql>
#include "articlewidget.h"
#include "stockwidget.h"
#include "intakewidget.h"
#include "outputwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:       
    bool connOpen()
    {
        if(!db.open())
        {
            qDebug() << "Cannot open database: " << db.lastError();
            return false;
        }
        return true;
    }

    void connClose()
    {
        db.close();
    }

    void setupOnCentre(QWidget*);
    void setBold(QWidget*);

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void logoutConfirmed();

public slots:
    void receiveLoginInfo (QString name, int group);

private slots:
    void pushButton_Article_clicked();
    void pushButton_Stock_clicked();
    void pushButton_Intake_clicked();
    void pushButton_Output_clicked();
    void logoutRequested();
    void closeTab(int);

private:
    int ugroup = 0;
    bool isLogged = false;
    QString uname;

    Ui::MainWindow *ui;
    QSqlDatabase db;

    QWidget *w;

    QPushButton *pushButton_Article;
    QPushButton *pushButton_Stock;
    QPushButton *pushButton_Intake;
    QPushButton *pushButton_Output;
    QPushButton *pushButton_Logout;

    QTabWidget *tabWgt;

    ArticleWidget *articleTab = nullptr;
    StockWidget *stockTab = nullptr;
    IntakeWidget *intakeTab = nullptr;
    OutputWidget *outputTab = nullptr;

    bool articleTab_Exists = false;
    bool stockTab_Exists = false;
    bool intakeTab_Exists = false;
    bool outputTab_Exists = false;
};
