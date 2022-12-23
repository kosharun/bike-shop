#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlQuery>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QSqlQueryModel *model;
    QString user_email, name, brojac;
private slots:
    void on_enterPushButton_clicked();

    void on_pushButton_clicked();

    void on_submitPushButton_clicked();

    void on_submitButton_clicked();

    void on_signInButton_clicked();

    void on_loginButton_clicked();

    void on_registerButton_clicked();

    void on_backButton4_clicked();

    void on_artikalSetButton_clicked();

    void on_backTable_clicked();

    void on_backArtikli_clicked();

    void on_atrikliButton_clicked();

    void on_pushButton_2_clicked();

    void on_realArticlesButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
