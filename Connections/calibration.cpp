#include "calibration.h"
#include "preform_light.h"
#include "preform_des_dll.h"
Calibration::Calibration(QObject *parent,Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m)
    : QObject{parent}
{
    Initalization(c,Z,m);
    pre = new Preform_light("preform_model.json");
    w=new Preform_des_dll("preform_model.json");
}

void Calibration::Initalization(Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m)
{
    Set_Machine_Manager(m);
    Set_CameraParameter(Z);
    Set_Camera_thread(c);
}

void Calibration::Start()
{
    // cameraparameter->Camera_Set_Grabber(camera->LiveGrabber);
    cameraparameter->Camera_Set_Grabbing_Senario(ZDS_camera_parameter::senario::triggerfreerun);
    machinemanager->SetMachineSenario(MachineManager::senario::calibration);
    connect(camera,SIGNAL(cameraImagesend_Live(HalconCpp::HImage*)),this,SLOT(onCameraImageSend(HalconCpp::HImage*)));
    camera->cond_Live=true;
    camera->start();
}

void Calibration::Stop()
{
disconnect(camera,SIGNAL(cameraImagesend_Live(HalconCpp::HImage*)),this,SLOT(onCameraImageSend(HalconCpp::HImage*)));
camera->cond_Live=false;
machinemanager->SetMachineSenario(MachineManager::senario::systemOff);
}

void Calibration::Set_Camera_thread(Camera_Live *m)
{
    camera = m;

}

void Calibration::Set_PIX_MM(double minpix2mmm, double maxpix2mm)
{
    PixToMM_max=maxpix2mm;
    PixToMM_min=minpix2mmm;
}

void Calibration::Set_Machine_Manager(MachineManager *m)
{
    machinemanager = m;
}

void Calibration::Set_CameraParameter(ZDS_camera_parameter *m)
{
    cameraparameter = m;
}

void Calibration::setnewOvalDim(double newmin, double newmax)
{
    PixToMM_min  =(newmin/OldOvalMin)*PixToMM_min;
    PixToMM_max  =(newmax/OldOvalMax)*PixToMM_max;
}

void Calibration::onCameraImageSend(HImage *im)
{
    pre->process(*im);
    qDebug()<<"calibration pre.score:....."<<pre->score<<"pix"<<PixToMM_max;
    if(pre->score > 0.9)
    {
        // Stop();
        w->process(*im,0,0,0,PixToMM_min);
        OldOvalMin=0;
        OldOvalMax=0;
        HImage image=w->get_image();
       emit CalibResultSend(&image,OldOvalMax,OldOvalMin);
    }
}
