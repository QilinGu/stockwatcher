#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(qApp->applicationDirPath()+"/warehouse.sqlite");

    ui->setupUi(this);

    w = new QWidget(this);

    pushButton_Article = new QPushButton(w);
    pushButton_Article->setText("Артикулы");
    setBold(pushButton_Article);
    pushButton_Article->setAutoDefault(true);

    pushButton_Stock = new QPushButton(w);
    pushButton_Stock->setText("Запас");
    setBold(pushButton_Stock);
    pushButton_Stock->setAutoDefault(true);

    pushButton_Intake = new QPushButton(w);
    pushButton_Intake->setText("Приемка");
    setBold(pushButton_Intake);
    pushButton_Intake->setAutoDefault(true);

    pushButton_Output = new QPushButton(w);
    pushButton_Output->setText("Выпуск");
    setBold(pushButton_Output);
    pushButton_Output->setAutoDefault(true);

    pushButton_Logout = new QPushButton(w);
    pushButton_Logout->setText("LOGOUT");
    setBold(pushButton_Logout);
    pushButton_Logout->setAutoDefault(true);

    tabWgt = new QTabWidget(w);
    tabWgt->setTabsClosable(true);
    tabWgt->setMovable(true);

    QVBoxLayout *vLay = new QVBoxLayout;
    vLay->setMargin(5);
    vLay->setSpacing(15);
    vLay->addWidget(pushButton_Article);
    vLay->addWidget(pushButton_Stock);
    vLay->addWidget(pushButton_Intake);
    vLay->addWidget(pushButton_Output);
    vLay->addWidget(pushButton_Logout);
    vLay->addStretch(1);

    QHBoxLayout *hLay = new QHBoxLayout;
    hLay->setMargin(5);
    hLay->setSpacing(15);
    hLay->addLayout(vLay);
    hLay->addWidget(tabWgt);

    w->setLayout(hLay);
    w->show();

    w->setTabOrder(pushButton_Article, pushButton_Stock);
    w->setTabOrder(pushButton_Stock, pushButton_Intake);
    w->setTabOrder(pushButton_Intake, pushButton_Output);
    w->setTabOrder(pushButton_Output, tabWgt);

    this->setWindowTitle("StockWatcher");
    this->setFixedSize(1024, 768);
    this->setCentralWidget(w);
    setupOnCentre(this);

    connect (pushButton_Article, SIGNAL(clicked()),
             SLOT(pushButton_Article_clicked()));
    connect (pushButton_Stock, SIGNAL(clicked()),
             SLOT(pushButton_Stock_clicked()));
    connect (pushButton_Intake, SIGNAL(clicked()),
             SLOT(pushButton_Intake_clicked()));
    connect (pushButton_Output, SIGNAL(clicked()),
             SLOT(pushButton_Output_clicked()));

    connect (pushButton_Logout, SIGNAL(clicked()),
             SLOT(logoutRequested()));

    connect (tabWgt, SIGNAL(tabCloseRequested(int)),
             SLOT(closeTab(int)));
}

MainWindow::~MainWindow()
{
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    delete ui;
}

void MainWindow::setupOnCentre(QWidget *wgt)
{
    QDesktopWidget desk;
    int deskWidth = desk.screen()->width();
    int deskHeight = desk.screen()->height();
    int width = wgt->width();
    int height = wgt->height();
    wgt->move(deskWidth/2 - width/2, deskHeight/2 - height/2);
}

void MainWindow::setBold(QWidget *wgt)
{
    QFont font(wgt->font());
    font.setBold(true);
    wgt->setFont(font);
}

void MainWindow::receiveLoginInfo(QString name, int group)
{
    uname = name;
    ugroup = group;
    isLogged = true;
    statusBar()->showMessage(uname);
}

void MainWindow::pushButton_Article_clicked()
{
    if(!articleTab_Exists)
    {
        articleTab = new ArticleWidget(tabWgt);
        tabWgt->addTab(articleTab, "Информация об артикуле");
        articleTab_Exists = true;
        tabWgt->setCurrentWidget(articleTab);
    }
    else
        tabWgt->setCurrentWidget(articleTab);
}

void MainWindow::pushButton_Stock_clicked()
{
    if(!stockTab_Exists)
    {
        stockTab = new StockWidget(tabWgt);
        tabWgt->addTab(stockTab, "Информация о товарном запасе");
        stockTab_Exists = true;
        tabWgt->setCurrentWidget(stockTab);
    }
    else
        tabWgt->setCurrentWidget(stockTab);
}

void MainWindow::pushButton_Intake_clicked()
{
    if(!intakeTab_Exists)
    {
        intakeTab = new IntakeWidget(tabWgt);
        tabWgt->addTab(intakeTab, "Приемка товара");
        intakeTab_Exists = true;
        tabWgt->setCurrentWidget(intakeTab);
    }
    else
        tabWgt->setCurrentWidget(intakeTab);
}

void MainWindow::pushButton_Output_clicked()
{
    if(!outputTab_Exists)
    {
        outputTab = new OutputWidget(tabWgt);
        tabWgt->addTab(outputTab, "Выпуск товара");
        outputTab_Exists = true;
        tabWgt->setCurrentWidget(outputTab);
    }
    else
        tabWgt->setCurrentWidget(outputTab);
}

void MainWindow::closeTab(int index)
{
    QString str = QString::fromUtf8(tabWgt->widget(index)->metaObject()->className());
    tabWgt->removeTab(index);

    if (str=="ArticleWidget")
    {
        articleTab_Exists = false;
        delete articleTab;
        articleTab = nullptr;
    }

    if (str=="StockWidget")
    {
        stockTab_Exists = false;
        delete stockTab;
        stockTab = nullptr;
    }

    if (str=="IntakeWidget")
    {
        intakeTab_Exists = false;
        delete intakeTab;
        intakeTab = nullptr;
    }

    if (str=="OutputWidget")
    {
        outputTab_Exists = false;
        delete outputTab;
        outputTab = nullptr;
    }
}

void MainWindow::logoutRequested()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Отмена авторизации", "Вы уверены, что хотите выйти?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        ugroup = 0;
        isLogged = false;
        uname.clear();
        this->hide();
        emit logoutConfirmed();
    }
}
