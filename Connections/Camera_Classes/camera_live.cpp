#include "camera_live.h"


Camera_Live::Camera_Live(QObject *parent) : QThread(parent)
{

}

void Camera_Live::Set_Grabber_name_Live(HFramegrabber *grabber)
{
    LiveGrabber = grabber;
}

void Camera_Live::run()
{
    qDebug()<<"in run live camera";



    if (LiveGrabber == nullptr) {
        qDebug() << "LiveGrabber is null!";
        return;
    }
    else {
        qDebug() << "LiveGrabber is valid. Proceeding with GrabImageStart.";
    }

    HString type;
    type="byte";
    QElapsedTimer timer;


    timer.start();


    LiveGrabber->GrabImageStart(-1);



    while(cond_Live==1){

        try{
        LiveImage.GrabImageAsync(*LiveGrabber,-1);
        emit cameraImagesend_Live(&LiveImage);
        LiveImage.WriteImage("tiff",0,"LASTIMG");
        }
        catch (HException except)
        {
            qDebug()<<"FL exception timeout";
            continue;
        }
    }
}

void Camera_Live::Close_Frame_Live()
{
    // LiveGrabber->CloseFramegrabber();
    //        LiveGrabber->Clear();
}
