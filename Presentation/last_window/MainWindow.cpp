#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    businessLogic = new BusinessLogic();


}

MainWindow::~MainWindow()
{
    delete ui;
    delete businessLogic;

}

void MainWindow::on_Add_pushButton_clicked()
{
    // try {
    //     item = new setting_db();
    //     item->set_key("set");
    //     item->set_value(123);
    //     test->Add(*item);
    // } catch (const std::exception &e) {
    //     qDebug() << "Exception occurred:" << e.what();
    // }
    // setting_table->Add("jak1_time",0.3);
    // businessLogic->setting_table->Add("lift_time",0.2536);
    // businessLogic->dbtools->Add();
    businessLogic->dbtools->Add("liftime",0.2536);



}


void MainWindow::on_Delete_pushButton_clicked()
{
    // test->Delete(1);
    // businessLogic->dbtools->Delete();


}


void MainWindow::on_Edit_pushButton_clicked()
{
   // setting_table->Update(2,"set",12321);

}


void MainWindow::on_Load_pushButton_clicked()
{
     // ui->tableView->setModel(businessLogic->setting_table->GetAll("setting"));
    ui->tableView->setModel(businessLogic->dbtools->GetAll());


}

