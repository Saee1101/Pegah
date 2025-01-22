#ifndef INSPECTION_H
#define INSPECTION_H

#include <QObject>
#include "Camera_Classes/camera_live.h"
#include"machinemanager.h"
#include "Camera_Classes/zds_camera_parameter.h"
#include "preform_light.h"
#include "preform_des_dll.h"
class Inspection : public QObject
{
    Q_OBJECT
public:
    explicit Inspection(QObject *parent,Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m);
    void Initalization(Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m);
    void Start();
    void Stop();
    void Get_Result();
    void Set_RejectFlag(bool ovalflag ,bool headflag, bool ringflag);
    void Set_Inspection_Param(double maxoval,double minoval,double ringtelorance,double headtelorance);
    void Set_PIX_MM(double minpix2mmm,double maxpix2mm);
    void Set_Machine_Manager(MachineManager* m);
    void Set_CameraParameter(ZDS_camera_parameter* m);
    void Set_Camera_thread(Camera_Live* m );
    MachineManager *machinemanager;
    Preform_light *pre;
    Preform_des_dll *w;
    Camera_Live *camera;
    ZDS_camera_parameter *cameraparameter;
    bool OvalFlag,HeadFlag,RingFlag;
    double PixToMM_min,PixToMM_max,Maxoval,Minoval,Ring_telorance,Head_telorance;
    bool AcceptFlag;
public slots:
    void onCameraImageSend(HalconCpp::HImage*);
signals:
    void InpectResultSend(HalconCpp::HImage* im,double lightscore ,double maxoval,double minoval,double headscore,double ringscore,bool AcceptFlag);
};

#endif // INSPECTION_H
