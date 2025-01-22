#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../BusinessLogic/BusinessLogic.h"
#include <QMainWindow>

#include <Cutelyst/Application>
#include <Cutelyst/Engine>
#include <Cutelyst/Server/server.h>

#include <Cutelyst/Context>
#include <Cutelyst/Response>
#include <Cutelyst/Server/server.h>

#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QSqlQuery>
#include <QSqlError>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_Add_pushButton_clicked();

    void on_Delete_pushButton_clicked();

    void on_Edit_pushButton_clicked();

    void on_Load_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    BusinessLogic* businessLogic;
};
#endif // MAINWINDOW_H
