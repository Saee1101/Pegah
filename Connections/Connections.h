#ifndef CONNECTIONS_H
#define CONNECTIONS_H
#define DllImport   __declspec( dllimport )
#include "Connections_global.h"
#include "inspection.h"
#include "calibration.h"
#include "machine.h"
#include "machinemanager.h"
#include "machinesetting.h"
#include "Camera_Classes/available_cameras.h"
#include "Camera_Classes/zds_camera_parameter.h"
#include "Camera_Classes/camera_live.h"
#include <QObject>
#include"preform_light.h"
using namespace HalconCpp;
class  Connections : public QObject
{
     Q_OBJECT
public:
    DllImport explicit Connections(QObject *parent = nullptr);
    Inspection* Inspection_;
    Calibration* Calibration_;
    plcmodbusconnect* plcmodbusconnect_;
    plcmodbusRW* plcmodbusRW_;
    Machine* Machine_;
    machinesetting* machinesetting_;
    MachineManager* MachineManager_;
    QStringList cameraname;
    Available_Cameras *Available_Cameras_;
    ZDS_camera_parameter *ZDS_camera_parameter_;
    Camera_Live*Camera_Live_;
     Preform_light *lighttester;
        int image_setting_counter=0;
    DllImport void Inspection_Start(QMap<QString, QString> *map);
    DllImport void Inspection_Stop();
    DllImport void Calibration_Start(QMap<QString, QString> *map);
    DllImport void Calibration_Stop();
    DllImport  bool Check_Plc();
    DllImport  void Disconnect_Plc();
    DllImport  bool Reconnect_Plc();
    DllImport  bool Check_Camera(int cameracount);
    DllImport  void Disconnect_Camera();
    DllImport  bool Reconnect_Camera(int cameracount);
    DllImport  void camera_init(QMap<QString, QString> *map);
    DllImport  bool Machin_init(QMap<QString, QString> *map);
    DllImport void IspectionInit();
    DllImport void CalibrationInit();
    DllImport void IspectionUpdate(QMap<QString, QString> *map);
    DllImport void CalibrationUpdate(QMap<QString, QString> *map);
    DllImport void MotorTest(int item,double speed,int direction,bool ONOFF);
    DllImport void JackTest(int item,double delaySetting,double TimeDur,int JacktestMode,bool ONOFF);
    DllImport void Camera_Start_Grabbing_Setting(int cameraGrabMode,bool ONOFF);
    DllImport void Camera_Exposure_Setting(double exposure);
    DllImport void Camera_Delay_Setting(double delay);
    DllImport void Camera_ROI_Setting(double width,double height,double xoffset,double yoffset);
    DllImport void Machie_Run(int mashine_senario);
    DllImport void UpdatePixmap(double New_Min_Pix_To_Mm,double New_Max_Pix_To_Mm);
    DllImport double grabLightScore(HImage* im);
    DllImport void HeartBitPlc();

    struct JacktestMode {
        static const int Jog=0;
        static const int Cycle=1;
        static const int Trigger=2;
    };
    struct CameraGrabMode {
        static const int Live=0;
        static const int Trigger=1;
    };
    struct Direction {
        static const bool forward=true;
        static const bool backward=false;
    };
    struct ONOFF {
        static const bool ON=true;
        static const bool OFF=false;
    };

public slots:
    void Inpection_Result_Recived(HalconCpp::HImage*,double lightscore ,double maxoval,
                                          double minoval,double headscore,double ringscore,bool AcceptFlag);
    void Calibration_Result_Recived(HalconCpp::HImage*,double maxoval ,double minoval);
    void Connection_SettingPreview(HalconCpp::HImage*);
signals:
    void ConnectionLayer_Inpection_Result(HalconCpp::HImage*,double lightscore ,double maxoval,
                                          double minoval,double headscore,double ringscore,bool AcceptFlag);
    void ConnectionLayer_Calibration_Result(HalconCpp::HImage*,double maxoval ,double minoval);
    void ConnectionLayer_Setting_Result(HalconCpp::HImage*);
    void failed_connects_C(QString error);
private :
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

#endif // CONNECTIONS_H
