#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QPixmap>
#include <string>

using namespace std;




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pic("C:/Users/KORISNIK/Desktop/Programmers/LITERATURA - Qt Creator/bike.png");
    ui->picLabel->setPixmap(pic);
    QPixmap pic2("C:/Users/KORISNIK/Desktop/Programmers/LITERATURA - Qt Creator/bike2.png");
    ui->picLabel2->setPixmap(pic2);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_enterPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_submitPushButton_clicked()
{
    QString email, password;
    QString emailLogin = ui->emailLogin->text();
    QString passwordLogin = ui->passwordLogin->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("sqlbikeshop");
    if (!db.open())
        QMessageBox::information(this,"A","fail");
    else
    {
        QSqlQuery mysql;
        mysql.exec("SELECT * FROM users");
        if (mysql.size() > 0)
        {
            while (mysql.next())
            {
                email = mysql.value("user_email").toString().toUtf8().constData();
                password = mysql.value("user_password").toString().toUtf8().constData();
                if (emailLogin == email && passwordLogin == password)
                {
                    name = mysql.value("user_name").toString().toUtf8().constData();
                    user_email = emailLogin;
                    int br = 0;
                    int BAM = 0;
                    if (mysql.value("user_email") == user_email)
                    {
                        br++;
                        BAM += mysql.value("bike_sell").toInt();
                    }
                    while(mysql.next())
                    {
                        if (mysql.value("user_email") == user_email)
                        {
                            br++;
                            BAM += mysql.value("bike_sell").toInt();
                        }
                    }
                    brojac = QString::number(BAM);
                    ui->stackedWidget->setCurrentIndex(3);
                    ui->welcomeLine->setText("Welcome " + name + "!");

                    if (br == 3)
                        ui->warning2Bikes->setText("Warning! There are only 2 bikes on market!");
                    ui->label_23->setText("Possible income: " + brojac + "KM");
                }
                else
                    ui->wrongPass->setText("Wrong password or email!");
            }
        }
    }
}


void MainWindow::on_submitButton_clicked()
{
    ui->lineEdit_2->setText("");
}

void MainWindow::on_signInButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_loginButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_registerButton_clicked()
{
    if (ui->username->text().size() < 2)
        QMessageBox::critical(this,"Username error","Username must be over 2 characters!");
    else
    {
        if (!ui->email->text().contains("@"))
            QMessageBox::critical(this,"Email error","Invalid email!");
        else
        {
            if (ui->password1->text() != ui->password2->text())
                QMessageBox::critical(this,"Password error","Passwords do not match!");
            else
            {
                QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
                db.setHostName("127.0.0.1");
                db.setUserName("root");
                db.setPassword("");
                db.setDatabaseName("sqlbikeshop");
                if (!db.open())
                    QMessageBox::information(this,"A","fail");
                else
                {
                    QString user_name ="'" + ui->username->text() + "'", user_email = "'" + ui->email->text() + "'", user_password = "'" + ui->password1->text() + "'";
                    QSqlQuery mysql;
                    mysql.bindValue(":user_name", user_name);
                    mysql.bindValue(":user_email", user_email);
                    mysql.bindValue(":user_password", user_password);
                    if(!mysql.exec("INSERT INTO users (user_name, user_email, user_password)"
                                   "VALUES (" + user_name + "," +  user_email + "," + user_password +");"))
                        QMessageBox::information(this,"a","fail exec");
                    else
                        ui->stackedWidget->setCurrentIndex(1);
                }
            }
        }
    }
}


void MainWindow::on_backButton4_clicked()
{
    ui->passwordLogin->setText("");
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_artikalSetButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_backTable_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_backArtikli_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_atrikliButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("sqlbikeshop");
    QSqlQueryModel *model = new QSqlQueryModel;
    if (!db.open())
        QMessageBox::critical(this,"fail","Failed to connect to database!");
    else
    {
        QSqlQuery *mysql = new QSqlQuery;
        mysql->prepare("SELECT user_id, user_name, bike_name, bike_bought, bike_sell, bike_gear  FROM users");
        mysql->exec();
        model->setQuery(*mysql);
        ui->tabela1->setModel(model);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if (ui->bikeNameLine->text().size() < 2)
        QMessageBox::critical(this,"Name error", "Invalid name!");
    else
        if (ui->bikeSellLine->text().size() < 1)
            QMessageBox::critical(this,"Selling error", "Invalid selling!");
        else
        {
            QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
            db.setHostName("127.0.0.1");
            db.setUserName("root");
            db.setPassword("");
            db.setDatabaseName("sqlbikeshop");
            if (!db.open())
                QMessageBox::critical(this,"fail","Failed to connect to database!");
            else
            {
                QString bName = "'" + ui->bikeNameLine->text() + "'";
                QString bGear = "'" + ui->bikeGearLine->text() + "'";
                QString bBought = "'" + ui->bikeBoughtLine->text() + "'";
                QString bSell = "'" + ui->bikeSellLine->text() + "'";

                QSqlQuery mysql;
                mysql.prepare("SET SQL_SAFE_UPDATES = 0;");
                mysql.exec();
                mysql.prepare( "INSERT INTO users(user_name, user_email, bike_name, bike_gear, bike_bought, bike_sell)"
                               "VALUES ('" +
                               name + "','" +
                               user_email + "'," +
                               bName + "," +
                               bGear + "," +
                               bBought + "," +
                               bSell + ")" );
                mysql.exec();
                mysql.exec("SELECT sum(bike_sell) FROM users WHERE user_email='" + this->user_email+ "'");
                mysql.next();
                ui->label_23->setText(mysql.value(0).toString());
                ui->stackedWidget->setCurrentIndex(3);
            }
        }
}


void MainWindow::on_realArticlesButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("sqlbikeshop");
    QSqlQueryModel *model = new QSqlQueryModel;
    if (!db.open())
        QMessageBox::critical(this,"fail","Failed to connect to database!");
    else
    {
        QSqlQuery *mysql = new QSqlQuery;
        mysql->prepare("SELECT user_id, user_name, bike_name, bike_bought, bike_sell, bike_gear  FROM users "
                       "WHERE user_email = '" + user_email + "'");
        mysql->exec();
        model->setQuery(*mysql);
        ui->tableViewArticles->setModel(model);
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

