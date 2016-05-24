#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    mainForm = new MainWindow();

    w = new QWidget(this);

    imgLabel = new QLabel(w);
    imgLabel->setPixmap(QPixmap(":/res/icons/login.png").scaled(80,80,Qt::KeepAspectRatio));

    loginLabel = new QLabel(w);
    loginLabel->setText("Имя пользователя");
    mainForm->setBold(loginLabel);

    passLabel = new QLabel(w);
    passLabel->setText("Пароль");
    mainForm->setBold(passLabel);

    lineEdit_username = new QLineEdit(w);
    lineEdit_password = new QLineEdit(w);
    lineEdit_password->setEchoMode(QLineEdit::Password);

    pushButton_login = new QPushButton(w);
    pushButton_login->setText("Войти");
    mainForm->setBold(pushButton_login);
    pushButton_login->setAutoDefault(true);

    QVBoxLayout *vLay1 = new QVBoxLayout;
    vLay1->setMargin(5);
    vLay1->setSpacing(15);
    vLay1->addWidget(loginLabel);
    vLay1->addWidget(passLabel);

    QVBoxLayout *vLay2 = new QVBoxLayout;
    vLay2->setMargin(5);
    vLay2->setSpacing(15);
    vLay2->addWidget(lineEdit_username);
    vLay2->addWidget(lineEdit_password);

    QHBoxLayout *hLay1 = new QHBoxLayout;
    hLay1->setMargin(5);
    hLay1->setSpacing(15);
    hLay1->addWidget(imgLabel);
    hLay1->addLayout(vLay1);
    hLay1->addLayout(vLay2);

    QHBoxLayout *hLay2 = new QHBoxLayout;
    hLay2->addStretch(1);
    hLay2->addWidget(pushButton_login);

    QVBoxLayout *vLay = new QVBoxLayout;
    vLay->setMargin(5);
    vLay->setSpacing(15);
    vLay->addLayout(hLay1);
    vLay->addLayout(hLay2);

    w->setLayout(vLay);
    w->show();

    w->setTabOrder(lineEdit_username, lineEdit_password);
    w->setTabOrder(lineEdit_password, pushButton_login);

    this->setWindowTitle("StockWatcher: Аутентификация");
    this->setFixedSize(450,250);
    this->setCentralWidget(w);

    mainForm->setupOnCentre(this);

    connect(pushButton_login, SIGNAL(clicked()),
            SLOT(pushButton_login_clicked()));

    connect (this, SIGNAL(sendLoginInfo(QString,int)),
             mainForm, SLOT(receiveLoginInfo(QString,int)));

    connect (mainForm, SIGNAL(logoutConfirmed()),
             SLOT (showLoginWindow()));
}

Login::~Login()
{    
    delete ui;
}

void Login::showLoginWindow()
{
    realname = "";
    group = 0;

    mainForm->setupOnCentre(this);
    lineEdit_username->clear();
    lineEdit_password->clear();
    lineEdit_username->setFocus();
    this->show();
}

void Login::pushButton_login_clicked()
{
    QString username, password;
    username = this->lineEdit_username->text();
    password = this->lineEdit_password->text();

    if(!mainForm->connOpen())
    {
        statusBar()->showMessage("База данных не подключена");
        return;
    }

    QSqlQuery *qry = new QSqlQuery;
    qry->prepare("select * from users where username=:username and password=:password");
    qry->bindValue(":username", username);
    qry->bindValue(":password", password);

    if(qry->exec())
    {
        int count=0;
        while(qry->next())
        {
            group = qry->value(2).toInt();
            realname = qry->value(3).toString();
            count++;
        }
        if(count==1)
        {
            QMessageBox::information(this, QString("Добро пожаловать"), QString("Здравствуйте, %0. Приятной работы в StockWatcher").arg(realname));
            emit sendLoginInfo(username, group);
            mainForm->connClose();
            mainForm->show();
            this->hide();
        }
        if(count>1)
        {
            mainForm->connClose();
            statusBar()->showMessage("Имя пользователя и пароль дублируются");
        }
        if(count<1)
        {
            mainForm->connClose();
            statusBar()->showMessage("Неверное имя пользователя или пароль");
        }
    }
}
