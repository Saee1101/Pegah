#include "zds_camera_parameter.h"

ZDS_camera_parameter::ZDS_camera_parameter(QObject *parent)
    : Camera_Parameter{parent}
{
}

void ZDS_camera_parameter::Camera_Set_Exposure(int exposure)const
{
    grabber->SetFramegrabberParam ( "ExposureAuto", "Off");
    grabber->SetFramegrabberParam ( "ExposureTime", exposure);
}

void ZDS_camera_parameter::Camera_Set_Grabbing_Mode(bool type) const
{
    // grabber->CloseFramegrabber();
    if(type==CommandType::hardware){
        grabber->SetFramegrabberParam ( "TriggerMode", "On");
    grabber->SetFramegrabberParam ( "TriggerSource", "Line1");
    }else{
        grabber->SetFramegrabberParam ( "TriggerMode", "Off");
    }
}

void ZDS_camera_parameter::Camera_Set_ROI(int xoffset, int yoffset, int width, int height) const
{
    grabber->SetFramegrabberParam ( "OffsetX", xoffset);
    grabber->SetFramegrabberParam ( "OffsetY", yoffset);
       grabber->SetFramegrabberParam ( "Width", width);
       grabber->SetFramegrabberParam ( "Height", height);




}

void ZDS_camera_parameter::Camera_Burst_Mode_Enable(bool s, int picturecount) const
{
    if(s)
     grabber->SetFramegrabberParam( "TriggerCount", picturecount);
}

void ZDS_camera_parameter::Camera_Set_FrameRate(int framerate) const
{
    grabber->SetFramegrabberParam  ( "AcquisitionFrameRateEnable", 1);
    grabber->SetFramegrabberParam  ( "AcquisitionFrameRate", framerate);
}

void ZDS_camera_parameter::Camera_Set_Grabbing_Senario(int senario) const
{

    if(senario==senario::triggerfreerun){
        Camera_Burst_Mode_Enable(false,0);
        Camera_Set_Grabbing_Mode(CommandType::hardware);
    }
    else if(senario==senario::softwarefreerun){
        Camera_Burst_Mode_Enable(false,0);
        Camera_Set_Grabbing_Mode(CommandType::software);
    }
}
