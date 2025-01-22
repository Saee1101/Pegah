#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H
#include "HalconCpp.h"
#include "HDevThread.h"
// #include "../Connections/inspection.h"
// #include "../Connections/machinemanager.h"
#include "BusinessLogic_global.h"
#include "../Entities/Repository.h"
#include "../Entities/setting_machine_db.h"
#include "../Entities/setting_user_db.h"
#include "../Entities/setting_camera_db.h"
#include "../Entities/setting_product_db.h"
#include "../Entities/setting_user_role_db.h"
#include <../Entities/accept_db.h>
#include <../Entities/reject_db.h>
#include "Connections.h"
#include <QScopedPointer>
#include <QObject>




#define DllImport   __declspec( dllimport )

using namespace HalconCpp;
class  BusinessLogic:public QObject
{
  Q_OBJECT
public:
 // BusinessLogic();
    DllImport   explicit BusinessLogic(QObject *parent = nullptr);


    QScopedPointer<Repository<setting_user_db>> CRUD_setting_user_db;
    QScopedPointer<Repository<setting_user_role_db>> CRUD_setting_user_role_db;
    QScopedPointer<Repository<setting_machine_db>> CRUD_setting_machine_db;
    QScopedPointer<Repository<setting_camera_db>> CRUD_setting_camera_db;
    QScopedPointer<Repository<setting_product_db>> CRUD_setting_product_db;
    QScopedPointer<Repository<accept_db>> CRUD_accept_db;
    QScopedPointer<Repository<reject_db>> CRUD_reject_db;
    Connections connectionlayer;
    DllImport void System_Set_Mode(int Mode);
    DllImport void Initial_System();
    DllImport void PlcConnection();
    DllImport void PlcDisconnection();
    DllImport void CameraReconnection();
    DllImport void CameraDisconnection();
    DllImport static BusinessLogic *getInstance();
    struct Mode {
        static const int Inspection=0;
        static const int calibration=1;
        static const int systemOff=2;
        static const int setting = 3;
    };
    DllImport void Check_Status(QVector<double> *machine_status);
    DllImport void Change_Pix_To_Mm(double new_min, double new_max);
    double Old_Min,Old_Max,new_Pix_To_MM_Min,new_Pix_To_MM_Max;
    bool Setting_Save_Image_Flag;
    int Setting_count_Image_Save=0;
    DllImport void Report_db();
    /////////////////////////////////
     DllImport void push_map ();
    QMap<QString,QString> dataMap_setting_machine_db;
    QMap<QString,QString> dataMap_setting_camera_db;
    QMap<QString,QString> dataMap_setting_product_db;
    QMap<QString,QString> dataMap_setting_user_db;
    QMap<QString,QString> dataMap_setting_user_role_db;
    QMap<QString,QString> dataMap_accept_db;
    QMap<QString,QString> dataMap_reject_db;
     public slots:
    void ConnectionLayer_Calibration_Result_Recived(HalconCpp::HImage*,double,double);
    void ConnectionLayer_Inpection_Result_Recived(HalconCpp::HImage*im,double lightscore ,double maxoval,
                                  double minoval,double headscore,double ringscore,bool AcceptFlag);
    void ConnectionLayer_Setting_Camera_Recived(HalconCpp::HImage*);
    void HandelConnectionError(const QString error_message);



signals:
   void failed_connects(QString);
   void send_image(HalconCpp::HImage* im);
   void sendInspectionResult(HalconCpp::HImage* im,double lightscore ,double maxoval,
                             double minoval,double headscore,double ringscore,bool AcceptFlag);
   void sendCalibrationResult(double maxoval,
                              double minoval);
   void lightscoresender(double score);
};
#endif // BUSINESSLOGIC_H
