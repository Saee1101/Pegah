#include "BusinessLogic.h"

BusinessLogic::BusinessLogic(QObject *parent) :  QObject{parent}
    ,CRUD_setting_user_db(new Repository<setting_user_db>())
    ,CRUD_setting_machine_db(new Repository<setting_machine_db>())
    ,CRUD_setting_camera_db(new Repository<setting_camera_db>())
    ,CRUD_setting_product_db(new Repository<setting_product_db>())
    ,CRUD_setting_user_role_db(new Repository<setting_user_role_db>())
    ,CRUD_reject_db(new Repository<reject_db>())
    ,CRUD_accept_db(new Repository<accept_db>())

{
    connect(&connectionlayer,SIGNAL(failed_connects_C(QString)),this,SLOT(HandelConnectionError(QString)));
}

void BusinessLogic::System_Set_Mode(int Mode)
{

    switch (Mode) {
    case Mode::Inspection:
        push_map();
        connect(&connectionlayer,SIGNAL(ConnectionLayer_Inpection_Result(HalconCpp::HImage*,double,double,
                                                                      double,double,double,bool))
                ,this,SLOT(ConnectionLayer_Inpection_Result_Recived(HalconCpp::HImage*,double,double,
                                                               double,double,double,bool)));
        connectionlayer.Inspection_Start(&dataMap_setting_product_db);
        break;

    case Mode::calibration:
        push_map();

        connect(&connectionlayer,SIGNAL(ConnectionLayer_Calibration_Result(HalconCpp::HImage*,double,double))
                ,this,SLOT(ConnectionLayer_Calibration_Result_Recived(HalconCpp::HImage*,double,double)));
        connectionlayer.Calibration_Start(&dataMap_setting_product_db);

        break;
    case Mode::setting:
        qDebug()<<"connectionlayer.Setting_Start()";
        connect(&connectionlayer,SIGNAL(ConnectionLayer_Setting_Result(HalconCpp::HImage*)),
                this,SLOT(ConnectionLayer_Setting_Camera_Recived(HalconCpp::HImage*)));
        break;
    case Mode::systemOff:
        qDebug()<<"connectionlayer.systemoff";
        connectionlayer.Calibration_Stop();
        connectionlayer.Inspection_Stop();
        disconnect(&connectionlayer,SIGNAL(ConnectionLayer_Inpection_Result(HalconCpp::HImage*,double,double,
                                                                          double,double,double,bool))
                ,this,SLOT(ConnectionLayer_Inpection_Result_Recived(HalconCpp::HImage*,double,double,
                                                               double,double,double,bool)));
        disconnect(&connectionlayer,SIGNAL(ConnectionLayer_Calibration_Result(HalconCpp::HImage*,double,double))
                ,this,SLOT(ConnectionLayer_Calibration_Result_Recived(HalconCpp::HImage*,double,double)));
        disconnect(&connectionlayer,SIGNAL(ConnectionLayer_Setting_Result(HalconCpp::HImage*)),
                this,SLOT(ConnectionLayer_Setting_Camera_Recived(HalconCpp::HImage*)));
        break;
    }
}


void BusinessLogic::Initial_System()
{
    qDebug()<< "BusinessLogic::Initial_System().";


     push_map();
    ///////////////////////////////

    // if (!dataMap_setting_machine_db.isEmpty()) {

    //     QMap<QString, QString>::iterator Iter = dataMap_setting_machine_db.begin();
    //     qDebug() << " Iter.value():"<< dataMap_setting_machine_db.value("Reject_Jack_Delay");
    //     while(Iter !=dataMap_setting_machine_db.end())
    //     {
    //         qDebug() << " key:" << Iter.key() << ", value:" << Iter.value();
    //         ++Iter;
    //     }

    // } else {
    //     qDebug() << "The dataMap_setting_machine_db is empty.";
    // }



     if(connectionlayer.Check_Plc() && connectionlayer.Check_Camera(1))
     {
    connectionlayer.Machin_init(&dataMap_setting_machine_db);
    connectionlayer.camera_init(&dataMap_setting_camera_db);
    connectionlayer.IspectionInit();
        connectionlayer.CalibrationInit();
    }


}

void BusinessLogic::PlcConnection()
{
    connectionlayer.Reconnect_Plc();
}

void BusinessLogic::PlcDisconnection()
{
    connectionlayer.Disconnect_Plc();
}

void BusinessLogic::CameraReconnection()
{
    connectionlayer.Reconnect_Camera(1);
}

void BusinessLogic::CameraDisconnection()
{
    connectionlayer.Disconnect_Camera();
}

BusinessLogic *BusinessLogic::getInstance()
{
    static BusinessLogic *instance=nullptr;
    if(instance==nullptr)
    {
        instance=new BusinessLogic();
    }
    return instance;
}

void BusinessLogic::Check_Status(QVector<double> *machine_status)
{
    if(!machine_status->isEmpty())
        machine_status->clear();
    machine_status->append(connectionlayer.Check_Camera(1));
    machine_status->append(connectionlayer.plcmodbusconnect_->modbusDevice->ConnectingState);

}

void BusinessLogic::Change_Pix_To_Mm(double new_min, double new_max)
{

    double old_pix_to_mm_min=dataMap_setting_product_db.value("pix_mm_min").toDouble();
    double old_pix_to_mm_max=dataMap_setting_product_db.value("pix_mm_max").toDouble();
     new_Pix_To_MM_Min=(old_pix_to_mm_min*new_min)/Old_Min;
     new_Pix_To_MM_Max=(old_pix_to_mm_max*new_max)/Old_Max;
     connectionlayer.UpdatePixmap(new_Pix_To_MM_Min,new_Pix_To_MM_Max);
     CRUD_setting_product_db->Update("pix_mm_min",QString::number(new_Pix_To_MM_Min));
     CRUD_setting_product_db->Update("pix_mm_max",QString::number(new_Pix_To_MM_Max));
}

void BusinessLogic::Report_db()
{

    QSqlTableModel* model_accept_db=CRUD_accept_db->GetAll();
    if (!model_accept_db) {
        qDebug()<< "Failed to retrieve data from model.";
    }
    for(int row =0;row <model_accept_db->rowCount();++row)
    {

        QString key=model_accept_db->data(model_accept_db->index(row,model_accept_db->fieldIndex("key_"))).toString();
        QString value=model_accept_db->data(model_accept_db->index(row,model_accept_db->fieldIndex("value_"))).toString();
        dataMap_accept_db.insert(key,value);

    }
    //////////////////////////////////////////////////
     QSqlTableModel* model_reject_db=CRUD_reject_db->GetAll();
    if (!model_reject_db) {
        qDebug()<< "Failed to retrieve data from model.";
    }
    for(int row =0;row <model_reject_db->rowCount();++row)
    {

        QString key=model_reject_db->data(model_reject_db->index(row,model_reject_db->fieldIndex("key_"))).toString();
        QString value=model_reject_db->data(model_reject_db->index(row,model_reject_db->fieldIndex("value_"))).toString();
        dataMap_reject_db.insert(key,value);

    }
}


void BusinessLogic::ConnectionLayer_Calibration_Result_Recived(HImage *im, double maxoval, double minoval)
{
    Old_Max=maxoval;
    Old_Min=minoval;
    emit send_image(im);
    emit sendCalibrationResult(maxoval,minoval);
}

void BusinessLogic::ConnectionLayer_Inpection_Result_Recived(HImage *im, double lightscore, double maxoval, double minoval, double headscore, double ringscore,bool AcceptFlag)
{
  emit send_image(im);
    emit sendInspectionResult(im,lightscore,maxoval,minoval,headscore,ringscore,AcceptFlag);
}

void BusinessLogic::ConnectionLayer_Setting_Camera_Recived(HImage *im)
{
  emit send_image(im);
    emit lightscoresender(connectionlayer.grabLightScore(im));
    if(Setting_Save_Image_Flag &&Setting_count_Image_Save>0 ){
      QString  saveimage_name = "results" + QString::number(Setting_count_Image_Save);
      im->WriteImage("tiff", 0, saveimage_name.toStdString().c_str());
        Setting_count_Image_Save--;
    }
}

void BusinessLogic::HandelConnectionError(QString error_message)

{
    emit failed_connects(error_message);
}

void BusinessLogic::push_map()
{

    QSqlTableModel* model_setting_machine_db = CRUD_setting_machine_db->GetAll();
    if (!model_setting_machine_db) {
        qDebug()<< "Failed to retrieve data from model.";
    }
    for(int row =0;row <model_setting_machine_db->rowCount();++row)
    {
        QString key=model_setting_machine_db->data(model_setting_machine_db->index(row,model_setting_machine_db->fieldIndex("key_"))).toString();
        QString value=model_setting_machine_db->data(model_setting_machine_db->index(row,model_setting_machine_db->fieldIndex("value_"))).toString();
        dataMap_setting_machine_db.insert(key,value);
    }
    /////////////////////////////////////////////////////////////////
    QSqlTableModel* model_setting_camera_db = CRUD_setting_camera_db->GetAll();
    if (!model_setting_camera_db) {
        qDebug()<< "Failed to retrieve data from model.";
    }
    for(int row =0;row <model_setting_camera_db->rowCount();++row)
    {
        QString key=model_setting_camera_db->data(model_setting_camera_db->index(row,model_setting_camera_db->fieldIndex("key_"))).toString();
        QString value=model_setting_camera_db->data(model_setting_camera_db->index(row,model_setting_camera_db->fieldIndex("value_"))).toString();
        dataMap_setting_camera_db.insert(key,value);
    }
    /////////////////////////////////////////////////
    QSqlTableModel* model_setting_product_db =CRUD_setting_product_db->GetAll();
    if (!model_setting_product_db) {
        qDebug()<< "Failed to retrieve data from model.";
    }
    for(int row =0;row <model_setting_product_db->rowCount();++row)
    {

        QString key=model_setting_product_db->data(model_setting_product_db->index(row,model_setting_product_db->fieldIndex("key_"))).toString();
        QString value=model_setting_product_db->data(model_setting_product_db->index(row,model_setting_product_db->fieldIndex("value_"))).toString();
        dataMap_setting_product_db.insert(key,value);

    }
    /////////////////////////////////////////
    QSqlTableModel* model_setting_user_db =CRUD_setting_user_db->GetAll();
    if (!model_setting_user_db) {
        qDebug()<< "Failed to retrieve data from model.";
    }
    for(int row =0;row <model_setting_user_db->rowCount();++row)
    {
        QString key=model_setting_user_db->data(model_setting_user_db->index(row,model_setting_user_db->fieldIndex("key_"))).toString();
        QString value=model_setting_user_db->data(model_setting_user_db->index(row,model_setting_user_db->fieldIndex("value_"))).toString();
        dataMap_setting_user_db.insert(key,value);
    }
    /////////////////////////////////////////////
    QSqlTableModel* model_setting_user_role_db=CRUD_setting_user_role_db->GetAll();
    if (!model_setting_user_role_db) {
        qDebug()<< "Failed to retrieve data from model.";
    }
    for(int row =0;row <model_setting_user_role_db->rowCount();++row)
    {
        QString key=model_setting_user_role_db->data(model_setting_user_role_db->index(row,model_setting_user_role_db->fieldIndex("key_"))).toString();
        QString value=model_setting_user_role_db->data(model_setting_user_role_db->index(row,model_setting_user_role_db->fieldIndex("value_"))).toString();
        dataMap_setting_user_role_db.insert(key,value);
    }

}






