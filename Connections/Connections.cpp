#include "Connections.h"

// Connections::Connections() {}
Connections::Connections(QObject *parent)
    : QObject{parent}
{
    plcmodbusconnect_ = new plcmodbusconnect(this);
    lighttester = new Preform_light("preform_model.json");
}
void Connections::Inspection_Start(QMap<QString, QString> *map)
{
    // inspection->Initalization();
    IspectionUpdate(map);
    Inspection_->Start();
}

void Connections::Inspection_Stop()
{
    Inspection_->Stop();
}

void Connections::Calibration_Start(QMap<QString, QString> *map)
{
    CalibrationUpdate(map);
    Calibration_->Start();
}

void Connections::Calibration_Stop()
{
    Calibration_->Stop();
}

bool Connections::Check_Plc()
{

    plcmodbusconnect_->PlcConnectionConfigFromJson("plcconnectionconfig.json");
        if(plcmodbusconnect_->PlcConnectionInit())
        {
            return true;
        }
        else{
            qDebug()<<"Connections::Check_Plc failed !!";
            emit failed_connects_C("PLC IS NOT CONNECTED .");
            return false;
        }
    // }else
    //     return true;
}

bool Connections::Reconnect_Plc()
{
    if(plcmodbusconnect_->PlcReconnection())
    {
        return true;
    }
    else{
        qDebug()<<"Connections::Check_Plc failed !!";
        emit failed_connects_C("PLC IS NOT CONNECTED .");
        return false;
    }
}

void Connections::Disconnect_Plc()
{
    plcmodbusconnect_->PlcDisConnect();
}

bool Connections::Check_Camera(int cameracount)
{

    try{
        Available_Cameras_ = new Available_Cameras(this);
        // qDebug()<<"Connections::Check_Camera()::camsize ";
        Available_Cameras_->cam_name_sender(&cameraname);
        if(cameraname.length()==cameracount)
        {
            qDebug()<<"Connections::Check_Camera() :: sucsess ::"<<cameraname.at(0);
            return true;
            // camera_init();
        }else
        {
            qDebug()<<"Connections::Check_Camera():: failed ";
            emit failed_connects_C("CAMERA IS NOT CONNECTED .");
            return false;
        }
    }
    catch (QString ex)
    {
        qDebug()<<"Connections::Check_Camera : "<<ex;
    }

}

void Connections::Disconnect_Camera()
{
    ZDS_camera_parameter_->grabber->Clear();
}

bool Connections::Reconnect_Camera(int cameracount)
{
    cameraname.clear();
    Available_Cameras_->cam_name_sender(&cameraname);
    if(cameraname.length()==cameracount)
    {
        qDebug()<<"Connections::Check_Camera() :: sucsess ::"<<cameraname.at(0);

        ZDS_camera_parameter_->Camera_Construction(cameraname.at(0));
        Camera_Live_->Set_Grabber_name_Live(ZDS_camera_parameter_->Camera_Get_Grabber());
         return true;
    }else
    {
        qDebug()<<"Connections::Check_Camera():: failed ";
        emit failed_connects_C("CAMERA IS NOT CONNECTED .");
        return false;
    }

}

void Connections::camera_init(QMap<QString, QString> *map)
{
    bool ok;
    ZDS_camera_parameter_ = new ZDS_camera_parameter(this);
    Camera_Live_ = new Camera_Live (this);
    ZDS_camera_parameter_->SetPlcModbusRW(plcmodbusRW_);
    ZDS_camera_parameter_->Camera_Construction(cameraname.at(0));
    Camera_Live_->Set_Grabber_name_Live(ZDS_camera_parameter_->Camera_Get_Grabber());
    ZDS_camera_parameter_->Camera_Trigger_Input_Delay_Address(map->value("Trigger_Input_Delay_Address").toInt(&ok,16));
    ZDS_camera_parameter_->Camera_Set_Delay(map->value("Delay").toInt());
    ZDS_camera_parameter_->Camera_Set_Exposure(map->value("Exposure").toInt());
    ZDS_camera_parameter_->Camera_Set_ROI(map->value("XOffset").toInt(),
                                          map->value("YOffset").toInt(),
                                          map->value("Width").toInt(),
                                          map->value("Height").toInt());
    ZDS_camera_parameter_->Camera_Set_FrameRate(map->value("FrameRate").toInt());
    ZDS_camera_parameter_->Camera_Set_Grabbing_Mode(ZDS_camera_parameter::CommandType::hardware);
    ZDS_camera_parameter_->Camera_Set_Grabbing_Senario(ZDS_camera_parameter::senario::triggerfreerun);

}

bool Connections::Machin_init(QMap<QString, QString> *map)
{
    plcmodbusRW_ =new plcmodbusRW(this,plcmodbusconnect_->getdevice());
    // plcmodbusRW_->WriteCoil(0x80e,true);
    Machine_=new Machine(this,plcmodbusRW_);
    machinesetting_=new machinesetting(this,Machine_);
    MachineManager_=new MachineManager(this,Machine_);
    Machine_->setMachineMap(2,1);
    QStringList jackjasonlist,motorjsonlist;
    jackjasonlist.append("jack1config.json");
    jackjasonlist.append("jack2config.json");
    motorjsonlist.append("StepMotor1config.json");
    Machine_->ReadMachineConfigFromJson(jackjasonlist,motorjsonlist);
    machinesetting_->UpdateJackSetting(0,map->value("Feed_Jack_Delay").toDouble(),
                                       map->value("Feed_Jack_Time").toDouble());
    machinesetting_->UpdateJackSetting(1,map->value("Reject_Jack_Delay").toDouble(),
                                       map->value("Reject_Jack_Time").toDouble());
    machinesetting_->UpdateMotorSetting(0,map->value("Star_Wheel_Speed").toDouble());
    MachineManager_->SetMachineSenario(MachineManager::senario::systemOff);
    MachineManager_->setrejectjack(1);
    return true;

}

void Connections::IspectionInit()
{
    Inspection_ = new Inspection(this,Camera_Live_,ZDS_camera_parameter_,MachineManager_);
    connect(Inspection_,SIGNAL(InpectResultSend(
                             HalconCpp::HImage*,double,double,
                             double,double,double,bool))
            ,this,SLOT(Inpection_Result_Recived(HalconCpp::HImage*,double,double,
                                          double,double,double,bool)));

}

void Connections::CalibrationInit()
{
    Calibration_ = new Calibration(this,Camera_Live_,ZDS_camera_parameter_,MachineManager_);
    connect(Calibration_,SIGNAL(CalibResultSend(
                              HalconCpp::HImage*,double,double))
            ,this,SLOT(Calibration_Result_Recived(HalconCpp::HImage*,double,double)));
}

void Connections::IspectionUpdate(QMap<QString, QString> *map)
{
    qDebug()<<"map->value(oval_on_off)"<<map->value("oval_on_off");
    Inspection_->Set_Inspection_Param(map->value("oval_max").toDouble(),map->value("oval_min").toDouble(),map->value("ring_defect").toDouble(),map->value("head_defect").toDouble());
    Inspection_->Set_RejectFlag(toBool(map->value("oval_on_off")),toBool(map->value("head_on_off")),toBool(map->value("ring_on_off")));
    Inspection_->Set_PIX_MM(map->value("pix_mm_min").toDouble(),map->value("pix_mm_max").toDouble());
}

void Connections::CalibrationUpdate(QMap<QString, QString> *map)
{

    Calibration_->Set_PIX_MM(map->value("pix_mm_min").toDouble(),map->value("pix_mm_max").toDouble());

}

void Connections::MotorTest(int item, double speed, int direction, bool ONOFF)
{
    if(ONOFF){
        machinesetting_->UpdateMotorSetting(item,speed);
        Machine_->motorlist.at(item)->JogOn(direction);
    }
    else{
        Machine_->motorlist.at(item)->JogOff();
    }
}

void Connections::JackTest(int item, double delaySetting, double TimeDur, int JacktestMode, bool ONOFF)
{
    if(ONOFF){
        machinesetting_->UpdateJackSetting(item,delaySetting,TimeDur);
        switch (JacktestMode) {
        case JacktestMode::Jog:
            Machine_->jacklist.at(item)->JogOn();
            break;
        case JacktestMode::Cycle:
            Machine_->jacklist.at(item)->CycleExecuteOn();
            break;
        case JacktestMode::Trigger:
            Machine_->jacklist.at(item)->triggerExecuteOn();
            break;
        }}else{
        Machine_->jacklist.at(item)->CycleExecuteOff();
        Machine_->jacklist.at(item)->triggerExecuteOff();
        Machine_->jacklist.at(item)->JogOff();
    }
}

void Connections::Camera_Start_Grabbing_Setting(int cameraGrabMode, bool ONOFF)
{
    if(ONOFF){
        if(cameraGrabMode==CameraGrabMode::Live){
            ZDS_camera_parameter_->Camera_Set_Grabbing_Senario(ZDS_camera_parameter::senario::softwarefreerun);
            // ZDS_camera_parameter_->Camera_Set_FrameRate(20);
        }else if(cameraGrabMode==CameraGrabMode::Trigger){
            ZDS_camera_parameter_->Camera_Set_Grabbing_Senario(ZDS_camera_parameter::senario::triggerfreerun);
            // ZDS_camera_parameter_->Camera_Set_FrameRate(5);
        }
        connect(Camera_Live_,SIGNAL(cameraImagesend_Live(HalconCpp::HImage*)),this,SLOT(Connection_SettingPreview(HalconCpp::HImage*)));
        qDebug()<<"setting start live................";    Camera_Live_->cond_Live=true;
        Camera_Live_->start();
    }else{
        disconnect(Camera_Live_,SIGNAL(cameraImagesend_Live(HalconCpp::HImage*)),this,SLOT(Connection_SettingPreview(HalconCpp::HImage*)));
        Camera_Live_->cond_Live=false;
    }
}

void Connections::Camera_Exposure_Setting(double exposure)
{
    ZDS_camera_parameter_->Camera_Set_Exposure(exposure);
}

void Connections::Camera_Delay_Setting(double delay)
{
    ZDS_camera_parameter_->Camera_Set_Delay(delay);
}

void Connections::Camera_ROI_Setting(double width, double height, double xoffset, double yoffset)
{
    if(Camera_Live_->cond_Live==false){
        ZDS_camera_parameter_->grabber->Clear();
        ZDS_camera_parameter_->Camera_Construction(cameraname.at(0));
        ZDS_camera_parameter_->Camera_Set_ROI(xoffset,yoffset,width,height);
        Camera_Live_->Set_Grabber_name_Live(ZDS_camera_parameter_->Camera_Get_Grabber());

    }
}

void Connections::Machie_Run(int mashine_senario)
{
    MachineManager_->SetMachineSenario(mashine_senario);
}

void Connections::UpdatePixmap(double New_Min_Pix_To_Mm, double New_Max_Pix_To_Mm)
{
    Calibration_->Set_PIX_MM(New_Min_Pix_To_Mm,New_Max_Pix_To_Mm);
}

double Connections::grabLightScore(HImage *im)
{
    lighttester->process(*im);
    return lighttester->score;
}

void Connections::HeartBitPlc()
{
    // plcmodbusconnect_->getdevice().
    // plcmodbusconnect_->getdevice().conn
}

void Connections::Inpection_Result_Recived(HImage *im, double lightscore, double maxoval, double minoval, double headscore, double ringscore,bool AcceptFlag)
{
    emit ConnectionLayer_Inpection_Result(im, lightscore , maxoval,minoval, headscore, ringscore,AcceptFlag);
}

void Connections::Calibration_Result_Recived(HImage *im, double maxoval, double minoval)
{
    emit ConnectionLayer_Calibration_Result(im,maxoval,minoval);
}

void Connections::Connection_SettingPreview(HImage *im)
{
    emit ConnectionLayer_Setting_Result(im);
}
