#include "inspection.h"

Inspection::Inspection(QObject *parent,Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m)
    : QObject{parent}
{
    Initalization(c,Z,m);
    pre = new Preform_light("preform_model.json");
    w=new Preform_des_dll("preform_model.json");
}

void Inspection::Initalization(Camera_Live* c,ZDS_camera_parameter* Z,MachineManager* m)
{
    Set_Machine_Manager(m);
    Set_CameraParameter(Z);
    Set_Camera_thread(c);
}

void Inspection::Start()
{
    // cameraparameter->Camera_Set_Grabber(camera->LiveGrabber);
    cameraparameter->Camera_Set_Grabbing_Senario(Camera_Parameter::senario::triggerfreerun);
    machinemanager->SetMachineSenario(MachineManager::senario::Inspection);
    connect(camera,SIGNAL(cameraImagesend_Live(HalconCpp::HImage*)),this,SLOT(onCameraImageSend(HalconCpp::HImage*)));
    camera->cond_Live=true;
    camera->start();
}

void Inspection::Stop()
{
    disconnect(camera,SIGNAL(cameraImagesend_Live(HalconCpp::HImage*)),this,SLOT(onCameraImageSend(HalconCpp::HImage*)));
    camera->cond_Live=false;
    machinemanager->SetMachineSenario(MachineManager::senario::systemOff);

}

void Inspection::Set_RejectFlag(bool ovalflag, bool headflag, bool ringflag)
{
    OvalFlag=!ovalflag;
    HeadFlag=!headflag;
    RingFlag=!ringflag;
}

void Inspection::Set_Inspection_Param(double maxoval, double minoval, double ringtelorance, double headtelorance)
{
    Minoval=minoval;
    Maxoval=maxoval;
    Ring_telorance=ringtelorance;
    Head_telorance=headtelorance;
}

void Inspection::Set_PIX_MM(double minpix2mmm, double maxpix2mm)
{
    PixToMM_max=maxpix2mm;
    PixToMM_min=minpix2mmm;
}

void Inspection::Set_Machine_Manager(MachineManager *m)
{
    machinemanager = m;
}

void Inspection::Set_CameraParameter(ZDS_camera_parameter *m)
{
    cameraparameter = m;
}

void Inspection::Set_Camera_thread(Camera_Live *m)
{
    camera = m ;
}


void Inspection::onCameraImageSend(HImage *im)
{


    pre->process(*im);
    if(pre->score > 0.9)
    {

       w->process(*im,Maxoval,Ring_telorance,Head_telorance,PixToMM_min);
 if(((w->get_flag_head()||HeadFlag)&&(w->get_flag_oval()||OvalFlag)&&(w->get_flag_ring()||RingFlag))==false){
            machinemanager->rejectsample();
            AcceptFlag=false;
        }else{
           AcceptFlag=true;
        }
        HImage image=w->get_image();
        emit InpectResultSend(&image, pre->score,w->get_score_oval(),w->get_dimeter(),w->get_score_head(),w->get_score_ring(),AcceptFlag);
    }else{
        AcceptFlag=false;
      qDebug()<<"this image rejecetd";
        emit InpectResultSend(im, pre->score,0,0,0,0,AcceptFlag);
    }

}
