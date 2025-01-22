#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <QDateTime>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include "BusinessLogic.h"
#include "gallery.h"
// #include <Cutelyst/Application>
// #include <Cutelyst/Engine>
// #include <Cutelyst/Server/server.h>

// #include <Cutelyst/Context>
// #include <Cutelyst/Response>
// #include <Cutelyst/Server/server.h>

#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
// #include "HalconCpp.h"
// #include "HDevThread.h"
#include <QSqlQuery>
#include <QSqlError>
#include "ShamciToMiladi.h"
#include <QObject>
#include "newplotclass.h"
#include "pieview.h"
#include "QProcess"
#include "ShamsiDateEdit.h"
#include <QSqlRecord>
#include <QFileDialog>
#include "xlsxdocument.h"
#include <QLabel>
#include <QPixmap>
#include <QImage>
using namespace HalconCpp;
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
    ShamsiDateEdit *newdate_From = new ShamsiDateEdit(this);
    ShamsiDateEdit *newdate_To = new ShamsiDateEdit(this);
    QDate date=QDate::currentDate();
    int year=date.year();
    int month=date.month();
    int day=date.day();
    ShamciToMiladi::SDATE sdate=shamcitomiladi_.MiladiToShamsi(month,day,year);
    bool isValidPassword(QString password);
    gallery* Setting_Gallery,*Reject_gallery;
    newplotclass *MaxOval_PLT,*MinOval_PLT,*HeadScore_PLT,*RingScore_PLT;
    bool SMT_SWS_MotorStartStop_PB_isON_OFF = true;
    bool SMT_FJ_StartStop_PB_IsON_OFF = true;
    bool SMT_RJ_StartStop_PB_IsON_OFF = true;
    bool SCT_CT_GRB_StartStop_PB_IsON_OFF = true;
    bool maxOval_HeadScore_Swithcer_PB_Flag=true;
    bool minOval_RingScore_Swithcer_PB_Flag=true;
    bool start_stop_pushButton_Flag=true;
    bool calibration_on_off_pushButton=true;
    bool statistics_pushButton=true;

    QVector<bool> User_Access_layer;
    void DesableEnableWidgets(QVector<bool>);

    QVector<bool> User_choose;
    void Page_choose(QVector<bool>);

    ShamciToMiladi shamcitomiladi_;
    void get_tabel_db_setting_machine(QMap<QString, QString> *map);
    void get_tabel_db_setting_camera(QMap<QString, QString> *map);
    void get_tabel_db_setting_product(QMap<QString, QString> *map);
    void CustomPlotDraw();
    pieview *statistic;
     QChartView *Statisticview;
    QProcess *keyboard;
    int acceptcount,rejectcount;
    QString user_current;
    // struct access_layer
    // {
    //     static const int normaluser=0;
    //     static const int admin=1;
    // };
    enum class access_Layer : int  {
         normaluser=0,
        admin=1
    };
    access_Layer get_Login_Info();
     void Set_Access(access_Layer);
    enum class pages_ : int
    {
         Statistic=0,
         Callibration=1,
         Status=2
     };
     void Set_page(pages_);
     void loadImageOnStartup();
private slots:
    void on_SUT_ADDUser_ADD_PB_clicked();



    void on_SCT_CT_SET_pushButton_clicked();

    void on_SPT__set_pushButton_clicked();

    void on_M_cp_set_pushButton_clicked();

    void on_SMT_SWS_MotorStartStop_PB_3_clicked();



    void on_SMT_FJ_StartStop_PB_3_clicked();

    void on_SMT_FJ_JogOnOff_PB_3_pressed();

    void on_SMT_FJ_JogOnOff_PB_3_released();

    void on_SMT_RJ_StartStop_PB_3_clicked();

    void on_SMT_RJ_JogOnOff_PB_3_pressed();


    void on_SMT_SWS_Motor_Set_PB_3_clicked();

    void on_SMT_SWS_FJ_Set_PB_3_clicked();

    void on_SMT_SWS_RJ_Set_PB_3_clicked();

    void on_SCT_CT_GRB_StartStop_PB_clicked();

    void on_SMT_RJ_JogOnOff_PB_3_released();

    void on_maxOval_HeadScore_Swithcer_PB_clicked();

    void on_minOval_RingScore_Swithcer_PB_clicked();

    void on_ST_save_pushButton_clicked();

    void on_M_sp_reset_pushButton_clicked();

    void on_M_parameter_keyboard_PB_clicked();

    void on_SUT_parameter_keyboard_PB_clicked();

    void on_SPT_parameter_keyboard_PB_clicked();

    void on_SCT_CT_parameter_keyboard_PB_clicked();

    void on_SCT_Machine_parameter_keyboard_PB_clicked();

    void on_M_start_stop_pushButton_clicked();

    void on_M_cp_calibration_on_off_pushButton_clicked();

    void on_M_cp__statistics_pushButton_clicked();

    void on_M_cp_status_pushButton_clicked();


    void on_ST_report_pushButton_clicked();

    void on_Machine_Setting_PB_clicked();

    void on_Camera_Setting_PB_clicked();

    void on_Product_Setting_PB_clicked();

    void on_User_Setting_PB_clicked();

    void on_Monitor_PB_clicked();

    void on_Setting_PB_clicked();

    void on_Statistic_PB_clicked();

    void on_Help_PB_clicked();

    void on_M_switch_user_pushButton_clicked();

    void on_M_power_pushButton_clicked();

    void on_LoginPage_keyboard_PB_clicked();

    void on_Login_PB_clicked();

    void on_shotDown_PB_clicked();

    void on_SUT_ChangeUser_SET_PB_clicked();

    void on_Reset_PB_clicked();

    void on_back_to_main_PB_clicked();

    void on_back_to_deckstop_PB_clicked();

    void on_plcconnection_CHB_checkStateChanged(const Qt::CheckState &arg1);

    void on_cameraconnection_CHB_checkStateChanged(const Qt::CheckState &arg1);

    void on_ST_keyboard_pushButton_clicked();

    void on_maxOval_HeadScore_Swithcer_PB_2_clicked();

    void on_minOval_RingScore_Swithcer_PB_2_clicked();

    void on_SCT_Sample_Image_pushButton_clicked();

public slots:
    void showErrorMessage(QString errorMessage);
    void recived_image(HalconCpp::HImage*);
    void Camera_Setting_Image_Recived(HImage*);
    void inspectionResultRecived(HalconCpp::HImage* im,double lightscore ,double maxoval,
                                 double minoval,double headscore,double ringscore,bool AcceptFlag);
    void CalibrationResultRecived(double maxoval,
                                  double minoval);
    void lightscoretestsetting(double score);
    void increaseDate();

private:
    Ui::MainWindow *ui;
    QTimer *timer ;
    QDateTime currentDateTime=QDateTime::currentDateTime();
    QGraphicsScene* scene;
    BusinessLogic businessLogic;
    halconqtwindow *inspection_image,*setting_image,*Reject_image;
    QString NewDate_To , NewDate_From;
    bool toBool(const QString& str) {
        QString lowerStr = str.trimmed().toLower();
        qDebug()<<"lowerStr : "<<lowerStr ;
        if (lowerStr == "true" || lowerStr == "1")
            return true;
        if (lowerStr == "false" || lowerStr == "0")
            return false;
        return false;
    }

};

#endif // MAINWINDOW_H
