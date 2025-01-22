#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QObject>
#include "Camera_Classes/camera_live.h"
#include"machinemanager.h"
#include "Camera_Classes/zds_camera_parameter.h"
#include "preform_light.h"
#include "preform_des_dll.h"
using namespace HalconCpp;

class Calibration : public QObject
{
    Q_OBJECT
public:
    explicit Calibration(QObject *parent ,Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m);
    void Initalization(Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m);
    void Start();
    void Stop();
    void Get_Result();
    void Set_Status();
    Camera_Live *camera;
    ZDS_camera_parameter *cameraparameter;
     Preform_light *pre;
    Preform_des_dll *w;
      void Set_Machine_Manager(MachineManager* m);
    void Set_CameraParameter(ZDS_camera_parameter* m);
    void Set_Camera_thread(Camera_Live* m );
    void Set_PIX_MM(double minpix2mmm,double maxpix2mm);
    MachineManager *machinemanager;
    void setnewOvalDim(double,double);
    double PixToMM_min,PixToMM_max,OldOvalMin,OldOvalMax;
public slots:
    void onCameraImageSend(HalconCpp::HImage*);

signals:
    void CalibResultSend(HalconCpp::HImage*,double,double);

};

#endif // CALIBRATION_H
