#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage help_Image(":/Tivanex - App Ui - Preform/HELP/Help - Preform App V.1.0.0-03.png");
    QLabel *help_Lable=new QLabel;
    help_Lable->setPixmap(QPixmap::fromImage(help_Image));
    ui->scrollArea->setWidget(help_Lable);
    //////////////////////
    loadImageOnStartup();
    ///////////////////////
   ui->stackedWidge_->setCurrentWidget(ui->Statistics);
    ui->stackedWidget->setCurrentWidget(ui->LoginPage);
   ui->Software_StackWidget->setCurrentWidget(ui->MonitorPage);
    ui->SettingStackWidget->setCurrentWidget(ui->MachineSettingPage);

    /////////////////////////////////
    inspection_image = new halconqtwindow(this);
    inspection_image->openwindow(350,260);
    ui->gridLayout_camera->addWidget(inspection_image);
    Reject_image = new halconqtwindow(this);
    Reject_image->openwindow(320,220);
    ui->gridLayout_rejectImageWindow->addWidget(Reject_image);
    setting_image = new halconqtwindow(this);
    setting_image->openwindow(330,300);
    ui->SCT_CP_CameraPreviewWindow_GRLY->addWidget(setting_image);
    // businessLogic=BusinessLogic::getInstance();


    connect(&businessLogic,SIGNAL(failed_connects(QString)),this,SLOT(showErrorMessage(QString)));
    connect(&businessLogic,SIGNAL(sendInspectionResult(HalconCpp::HImage*,double,double,double,double,double,bool)),
            this,SLOT(inspectionResultRecived(HalconCpp::HImage*,double,double,double,double,double,bool)));
    connect(&businessLogic,SIGNAL(sendCalibrationResult(double,double)),
            this,SLOT(CalibrationResultRecived(double,double)));
    connect(&businessLogic,SIGNAL(lightscoresender(double)),this,SLOT(lightscoretestsetting(double)));
    //////////////////////////////////////////////////////
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        ui->M_date_time_label->setText(QString::number( sdate.iYear) +"/"+QString::number( sdate.iMonth)
                                       +"/"+ QString::number(sdate.iDay)
                                       +" "+QDateTime::currentDateTime().toString("hh:mm:ss"));
        ui->ST_date_time_label->setText(QString::number( sdate.iYear) +"/"+QString::number(sdate.iMonth)
                                        +"/"+ QString::number(sdate.iDay)
                                        +" "+QDateTime::currentDateTime().toString("hh:mm:ss"));
    });
    timer->start(1000);
    /////////////////////////////////////////////////

    newdate_From->currentYear=1403;
    connect(newdate_From, &ShamsiDateEdit::dateChanged,[this](const QString &newDate_from){
        NewDate_From=newDate_from;
    });

       connect(newdate_From,&ShamsiDateEdit::increase,this,[=](int i){
           switch (i) {
           case 0:
               newdate_From->currentYear++;
               newdate_From->updateLineEdit();
               return;
           case 5:

               if(newdate_From->currentMonth<12)
               {

                   newdate_From->currentMonth++;
                   newdate_From->updateLineEdit();
                   break;
               }
               else
               {

                   newdate_From->currentMonth=1;
                   newdate_From->updateLineEdit();
                   break;
               }
           case 8:

               if(newdate_From->currentDay<31)
               {
                   newdate_From->currentDay++;
                   newdate_From->updateLineEdit();
                   break;
               }
               else
               {
                   newdate_From->currentDay=1;
                   newdate_From->updateLineEdit();
                   break;
               }
           }
       });

       connect(newdate_From,&ShamsiDateEdit::decrease,this,[=](int j){
           switch (j) {
           case 0:
               newdate_From->currentYear--;
               newdate_From->updateLineEdit();
               return;
           case 5:

               if(newdate_From->currentMonth>1)
               {

                   newdate_From->currentMonth--;
                   newdate_From->updateLineEdit();
                   break;
               }
               else
               {

                   newdate_From->currentMonth=12;
                   newdate_From->updateLineEdit();
                   break;
               }
           case 8:

               if(newdate_From->currentDay>1)
               {
                   newdate_From->currentDay--;
                   newdate_From->updateLineEdit();
                   break;
               }
               else
               {
                   newdate_From->currentDay=31;
                   newdate_From->updateLineEdit();
                   break;
               }
           }
       });
       ui->Date_From_gridLayout->addWidget(newdate_From,1,1);
    ///////////////////////////////////////////////

    newdate_To->currentYear=sdate.iYear;
    newdate_To->currentMonth=sdate.iMonth;
    newdate_To->currentDay=sdate.iDay;
    newdate_To->updateLineEdit();
    connect(newdate_To, &ShamsiDateEdit::dateChanged, [this](const QString &newDate_to) {
        NewDate_To=newDate_to;
    });
    connect(newdate_To,&ShamsiDateEdit::increase,this,[=](int i){
        switch (i) {
        case 0:
            newdate_To->currentYear++;
            newdate_To->updateLineEdit();
            return;
        case 5:

            if(newdate_To->currentMonth<12)
            {

                newdate_To->currentMonth++;
                newdate_To->updateLineEdit();
                break;
            }
            else
            {

                newdate_To->currentMonth=1;
                newdate_To->updateLineEdit();
                break;
            }
        case 8:

            if(newdate_To->currentDay<31)
            {
                newdate_To->currentDay++;
                newdate_To->updateLineEdit();
                break;
            }
            else
            {
                newdate_To->currentDay=1;
                newdate_To->updateLineEdit();
                break;
            }
        }
        });

    connect(newdate_To,&ShamsiDateEdit::decrease,this,[=](int j){
        switch (j) {
        case 0:
            newdate_To->currentYear--;
            newdate_To->updateLineEdit();
            return;
        case 5:

            if(newdate_To->currentMonth>1)
            {

                newdate_To->currentMonth--;
                newdate_To->updateLineEdit();
                break;
            }
            else
            {

                newdate_To->currentMonth=12;
                newdate_To->updateLineEdit();
                break;
            }
        case 8:

            if(newdate_To->currentDay>1)
            {
                newdate_To->currentDay--;
                newdate_To->updateLineEdit();
                break;
            }
            else
            {
                newdate_To->currentDay=31;
                newdate_To->updateLineEdit();
                break;
            }
        }
    });

    ui->Date_To_gridLayout->addWidget( newdate_To,1,1);

//////////////////////////////////////////////////////////////////////////////////

    ////////////  make plot MAX Label ///////////////////
    // scene =new QGraphicsScene(this);
    ////////////  make Reject Images Label ///////////////////
    // scene =new QGraphicsScene(this);
    // ui->ST_reject_Image_graphicView->setScene(scene);
    // // ui->ST_reject_Images_label->setParent(nullptr);
    // // ui->st_re
    // ui->ST_reject_Images_lable->setParent(nullptr);
    // QGraphicsProxyWidget* widget_3=scene->addWidget(ui->ST_reject_Images_lable);
    // widget_3->setRotation(90);

    /////////////////////////////////////////////////

    Setting_Gallery = new gallery(this,ui->SCT_G_PicThumbnails_LW);
    Reject_gallery = new gallery(this,ui->ST_Rejact_Gallery_Thumbnails_LW);
    Setting_Gallery->set_window(setting_image);
    Reject_gallery->set_window(Reject_image);
    Setting_Gallery->Set_ItemGallery(20,50,50,3);
    Reject_gallery->Set_ItemGallery(30,90,90,10);
//////////////////////////////////////////////
///
    statistic = new pieview;
    Statisticview= new QChartView(statistic);
    rejectcount = 1;
    acceptcount = 1;
    Statisticview->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout_statistic->addWidget(Statisticview);
    Statisticview->setBackgroundBrush(QBrush(QColor(44,44,44)));
    statistic->series->slices().at(0)->setValue(acceptcount);
    statistic->series->slices().at(1)->setValue(rejectcount);
    statistic->series->setHorizontalPosition(0.5);
    statistic->series->setVerticalPosition(0.5);
////////////////////////////////////////
     keyboard = new QProcess(this);
     keyboard->start("FreeVK.exe");
    //////////////////////////////////////////////////////////////
    ///

    businessLogic.Initial_System();
    get_tabel_db_setting_machine(&businessLogic.dataMap_setting_machine_db);
    get_tabel_db_setting_camera(&businessLogic.dataMap_setting_camera_db);
    get_tabel_db_setting_product(&businessLogic.dataMap_setting_product_db);
    ///////////////////////////////////////////////////
    ///

    CustomPlotDraw();

}

MainWindow::~MainWindow()
{
    delete ui;
    businessLogic.connectionlayer.Camera_Live_->LiveGrabber->Clear();
}

bool MainWindow::isValidPassword(QString password)
{

    //  It is between 1-10 characters
    if(password.length()<1 || password.length()>10)
    {
        QMessageBox messageBox(QMessageBox::Critical,
                               "WARNING!",
                               "It is between 1-10 characters",
                               QMessageBox::Ok,
                               this);

    }
    bool containsSpecialChatacter=true;
    for(int i=0;i<password.length();i++)
    {
        QChar ch=password[i];
        //  It is Letter Or Number
        if(!ch.isLetterOrNumber())
        {
            QMessageBox messageBox(QMessageBox::Critical,
                                   "WARNING!",
                                   "It is Letter Or Number",
                                   QMessageBox::Ok,
                                   this);
            containsSpecialChatacter=false;
        }
    }
    return containsSpecialChatacter;
}

void MainWindow::DesableEnableWidgets(QVector<bool> access)
{

    ui->Monitor_PB->setVisible(access.at(0));
    ui->Setting_PB->setVisible(access.at(1));
    ui->Statistic_PB->setVisible(access.at(2));

    // ui->MainSettingTab->setDisabled(access.at(0));
    // ui->SettingCameraTab->setDisabled(access.at(1));
    // ui->SettingMachineTab->setDisabled(access.at(2));
    // ui->SettingProductTab->setDisabled(access.at(3));
}

void MainWindow::Set_Access(access_Layer access)
{
    switch (access) {
    case access_Layer::normaluser:
        User_Access_layer={1,0,0};
         // ui->SUT_ChangeUser_AccessLevel_LB->setText("User");

        break;
    case access_Layer::admin:
        User_Access_layer={1,1,1};
        // ui->SUT_ChangeUser_AccessLevel_LB->setText("Admin");
        break;

    }
    DesableEnableWidgets(User_Access_layer);
}

void MainWindow::Set_page(pages_ choose_)
{

    switch (choose_) {
    case pages_::Statistic:
        ui->M_cp__statistics_pushButton->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 382.png);");
        ui->M_cp_calibration_on_off_pushButton->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 381.svg);");
        ui->M_cp_status_pushButton->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 380.png);");

        break;
    case pages_::Callibration:
        ui->M_cp__statistics_pushButton->setStyleSheet("border-image:url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Group 386.svg);");
        ui->M_cp_calibration_on_off_pushButton->setStyleSheet("image:url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Group 387.svg);");
        ui->M_cp_status_pushButton->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 380.png);");
        break;
    case pages_::Status:
        ui->M_cp__statistics_pushButton->setStyleSheet("border-image:url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Group 386.svg);");
        ui->M_cp_calibration_on_off_pushButton->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 381.svg);");
        ui->M_cp_status_pushButton->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-3/Group 386.svg);");
        break;
    }

}




void MainWindow::on_SUT_ADDUser_ADD_PB_clicked()
{
    if(ui->SUT_ADDUser_username_LE->text().isEmpty() || ui->SUT_ADDUser_password_LE->text().isEmpty())
    {
        QMessageBox messageBox2(QMessageBox::Critical,
                                "WARNING!",
                                "UserName or Password is Empty.",
                                QMessageBox::Ok ,
                                this);
        messageBox2.exec();
    }

    else if(isValidPassword(ui->SUT_ADDUser_password_LE->text()))
    {

        QMessageBox messageBox1(QMessageBox::Critical,
                                "WARNING!",
                                "You are '"+ui->SUT_ADDUser_AcessLevel_CB->currentText()+"'"
                                    +". Are you sure ?",
                                QMessageBox::No | QMessageBox::Yes ,
                                this);

        if (messageBox1.exec() == QMessageBox::Yes) {
            if(ui->SUT_ADDUser_password_LE->text()==ui->SUT_ADDUser_passwordValid_LE_2->text())
            {

                businessLogic.CRUD_setting_user_db->Add(ui->SUT_ADDUser_username_LE->text(),
                                                        ui->SUT_ADDUser_password_LE->text());
                businessLogic.CRUD_setting_user_role_db->Add(ui->SUT_ADDUser_username_LE->text(),
                                                             ui->SUT_ADDUser_AcessLevel_CB->currentText());
                ui->SUT_ADDUser_passwordValid_LE_2->setText("");
                ui->SUT_ADDUser_password_LE->setText("");
                ui->SUT_ADDUser_username_LE->setText("");
                businessLogic.push_map();
                messageBox1.close();
            }
            else
            {
                QMessageBox messageBox2(QMessageBox::Critical,
                                        "WARNING!",
                                        "Password not ecqual PasswordValid",
                                        QMessageBox::Ok ,
                                        this);
                messageBox2.exec();

            }
        }
    }


}






void MainWindow::on_SPT__set_pushButton_clicked()
{
    businessLogic.CRUD_setting_product_db->Update("oval_max",ui->SPT_OvalMax_SPB->text());
    businessLogic.CRUD_setting_product_db->Update("oval_min",ui->SPT_OvalMin_SPB->text());
    businessLogic.CRUD_setting_product_db->Update("head_defect",ui->SPT_HeadScore_SPB->text());
    businessLogic.CRUD_setting_product_db->Update("ring_defect",ui->SPT_RingScore_SPB->text());
    businessLogic.CRUD_setting_product_db->Update("oval_on_off",ui->SPT_Ovalreject_ON_OFF_CHB->isChecked()? "true" : "false");
    businessLogic.CRUD_setting_product_db->Update("ring_on_off",ui->SPT_Ringreject_ON_OFF_CHB->isChecked()? "true" : "false");
    businessLogic.CRUD_setting_product_db->Update("head_on_off",ui->SPT_Headreject_ON_OFF_CHB->isChecked()? "true" : "false");
    ui->gridLayout_plot_RingScore->removeWidget(RingScore_PLT);
    ui->gridLayout_plot_HeadScore->removeWidget(HeadScore_PLT);
    ui->gridLayout_plot_max->removeWidget(MaxOval_PLT);
    ui->gridLayout_plot_min->removeWidget(MinOval_PLT);
    qInfo()<<"product with oval"<<ui->SPT_OvalMax_SPB->text()<<"and diameter:"<<ui->SPT_OvalMin_SPB->text()
            <<"and head defect:"<<ui->SPT_HeadScore_SPB->text()<<"and ring defect:"<<ui->SPT_RingScore_SPB->text()
            <<"and ovalflag"<<ui->SPT_Ovalreject_ON_OFF_CHB->isChecked()
            <<"and Ringflag"<<ui->SPT_Ringreject_ON_OFF_CHB->isChecked()
            <<"and Headflag"<<ui->SPT_Headreject_ON_OFF_CHB->isChecked();

    CustomPlotDraw();

}


void MainWindow::on_M_cp_set_pushButton_clicked()
{

    businessLogic.Change_Pix_To_Mm(ui->M_cp_MIN_doubleSpinBox->text().toDouble()
                                   ,ui->M_cp_MAX_doubleSpinBox->text().toDouble());

}



void MainWindow::on_SMT_SWS_MotorStartStop_PB_3_clicked()
{


    if(SMT_SWS_MotorStartStop_PB_isON_OFF==true)
    {
        ui->SMT_SWS_MotorStartStop_PB_3->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 220-1.svg);");

        businessLogic.connectionlayer.MotorTest(0,ui->SMT_SWS_MotorSpeed_SP_3->value()
                                                ,ui->SMT_SWS_MotorDirection_CHB_3->isChecked(),Connections::ONOFF::ON);
        ui->SMT_SWS_MotorSpeed_SP_3->setVisible(false);
        ui->SMT_SWS_MotorSpeed_SP_3->setEnabled(false);
        ui->Monitor_PB->setVisible(false);
        ui->Statistic_PB->setVisible(false);
        SMT_SWS_MotorStartStop_PB_isON_OFF=false;
    }
    else
    {
        ui->SMT_SWS_MotorStartStop_PB_3->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 219.svg);");

        businessLogic.connectionlayer.MotorTest(0,ui->SMT_SWS_MotorSpeed_SP_3->value()
                                                ,ui->SMT_SWS_MotorDirection_CHB_3->isChecked(),Connections::ONOFF::OFF);
        ui->SMT_SWS_MotorSpeed_SP_3->setVisible(true);
         ui->SMT_SWS_MotorSpeed_SP_3->setEnabled(true);
       ui->Monitor_PB->setVisible(true);
        ui->Statistic_PB->setVisible(true);
        SMT_SWS_MotorStartStop_PB_isON_OFF=true;
    }

}
void MainWindow::on_SMT_SWS_Motor_Set_PB_3_clicked()
{
    qInfo()<<"update speed"<<ui->SMT_SWS_MotorSpeed_SP_3->text();
    if(ui->SMT_SWS_MotorSpeed_SP_3->text()!="0.0" ){
        businessLogic.CRUD_setting_machine_db->Update("Star_Wheel_Speed",ui->SMT_SWS_MotorSpeed_SP_3->text());
    }
}
void MainWindow::on_SMT_FJ_StartStop_PB_3_clicked()
{
    if(SMT_FJ_StartStop_PB_IsON_OFF==true)
    {
        ui->SMT_FJ_StartStop_PB_3->setStyleSheet("	border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 220-1.svg);");
        businessLogic.connectionlayer.JackTest(0,ui->SMT_FJ_Delay_SB_3->text().toDouble(),ui->SMT_FJ_Time_SB_3->text().toDouble()
                                               ,Connections::JacktestMode::Cycle,Connections::ONOFF::ON);

        qInfo()<<"feed jack start with delay:"<<ui->SMT_FJ_Delay_SB_3->text()<<"and time:"<<ui->SMT_FJ_Time_SB_3->text();

        ui->Monitor_PB->setVisible(false);
        ui->Statistic_PB->setVisible(false);
        SMT_FJ_StartStop_PB_IsON_OFF=false;
    }
    else
    {
        qInfo()<<"feed jack stop with delay:"<<ui->SMT_FJ_Delay_SB_3->text()<<"and time:"<<ui->SMT_FJ_Time_SB_3->text();

                ui->SMT_FJ_StartStop_PB_3->setStyleSheet("	border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 219-1.svg);");
        businessLogic.connectionlayer.JackTest(0,ui->SMT_FJ_Delay_SB_3->text().toDouble(),ui->SMT_FJ_Time_SB_3->text().toDouble()
                                               ,Connections::JacktestMode::Cycle,Connections::ONOFF::OFF);
                ui->Monitor_PB->setVisible(true);
                ui->Statistic_PB->setVisible(true);
        SMT_FJ_StartStop_PB_IsON_OFF=true;
    }
}

void MainWindow::on_SMT_FJ_JogOnOff_PB_3_pressed()
{
    businessLogic.connectionlayer.JackTest(0,ui->SMT_FJ_Delay_SB_3->text().toDouble(),ui->SMT_FJ_Time_SB_3->text().toDouble()
                                           ,Connections::JacktestMode::Jog,Connections::ONOFF::ON);
}

void MainWindow::on_SMT_FJ_JogOnOff_PB_3_released()
{
    businessLogic.connectionlayer.JackTest(0,ui->SMT_FJ_Delay_SB_3->text().toDouble(),ui->SMT_FJ_Time_SB_3->text().toDouble()
                                           ,Connections::JacktestMode::Jog,Connections::ONOFF::OFF);
}
void MainWindow::on_SMT_SWS_FJ_Set_PB_3_clicked()
{
    businessLogic.CRUD_setting_machine_db->Update("Feed_Jack_Delay",ui->SMT_FJ_Delay_SB_3->text());
    businessLogic.CRUD_setting_machine_db->Update("Feed_Jack_Time",ui->SMT_FJ_Time_SB_3->text());

}
void MainWindow::on_SMT_RJ_StartStop_PB_3_clicked()
{
    ui->SMT_RJ_StartStop_PB_3->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 219-1.svg);");
    businessLogic.connectionlayer.JackTest(1,ui->SMT_RJ_Delay_SB_3->text().toDouble(),ui->SMT_RJ_Time_SB_3->text().toDouble()
                                           ,Connections::JacktestMode::Trigger,Connections::ONOFF::ON);
    qInfo()<<"reject jack start with delay:"<<ui->SMT_RJ_Delay_SB_3->text()<<"and time:"<<ui->SMT_RJ_Time_SB_3->text();

}

void MainWindow::on_SMT_RJ_JogOnOff_PB_3_pressed()
{
    businessLogic.connectionlayer.JackTest(1,ui->SMT_RJ_Delay_SB_3->text().toDouble(),ui->SMT_RJ_Time_SB_3->text().toDouble()
                                           ,Connections::JacktestMode::Jog,Connections::ONOFF::ON);
}
void MainWindow::on_SMT_SWS_RJ_Set_PB_3_clicked()
{
    businessLogic.CRUD_setting_machine_db->Update("Reject_Jack_Delay",ui->SMT_RJ_Delay_SB_3->text());
    businessLogic.CRUD_setting_machine_db->Update("Reject_Jack_Time",ui->SMT_RJ_Time_SB_3->text());
}
void MainWindow::showErrorMessage( QString errorMessage)
{
    QMessageBox messageBox(QMessageBox::Critical,
                           "WARNING!",
                           errorMessage,
                           QMessageBox::Retry |QMessageBox::Cancel,
                           this);

    if (messageBox.exec() == QMessageBox::Retry) {
        businessLogic.Initial_System();
    }else{
       MainWindow::~MainWindow();
    }

}


void MainWindow::recived_image(HImage *im)
{
    Hlong Width,Height;
    im->GetImageSize(&Width,&Height);
    // AI_image_CL->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
    inspection_image->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
    if(*im->CountChannels().ToDArr()>2)
    im->DispColor(inspection_image->WinfoeID());
    else
    im->DispImage(inspection_image->WinfoeID());
}

void MainWindow::Camera_Setting_Image_Recived(HImage *im)
{

    Hlong Width,Height;
    im->GetImageSize(&Width,&Height);
    // AI_image_CL->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
    setting_image->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
    im->DispImage(setting_image->WinfoeID());
    Setting_Gallery->Add_Image(im);
}

void MainWindow::inspectionResultRecived(HalconCpp::HImage* im,double lightscore, double maxoval, double minoval, double headscore, double ringscore, bool AcceptFlag)
{
    ui->White_Indicator_Status_LB->setText(QString::number(lightscore));
    MaxOval_PLT->setData(maxoval);
    MinOval_PLT->setData(minoval);
    HeadScore_PLT->setData(headscore);
    RingScore_PLT->setData(ringscore);
    Reject_gallery->Add_Image(im);
    if(AcceptFlag){
        ui->M_cp_accept_reject_Label->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 299.svg);");
        acceptcount++;
        ui->Accept_Count_LB->setText(QString::number(acceptcount));
        statistic->series->slices().at(0)->setValue(acceptcount);
    }else{
        ui->M_cp_accept_reject_Label->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 435.svg);");
        rejectcount++;
        ui->Reject_Count_LB->setText(QString::number(rejectcount));
        statistic->series->slices().at(1)->setValue(rejectcount);
     }
    if(QDateTime::currentDateTime().time().hour()==23 && QDateTime::currentDateTime().time().minute()==59
         && QDateTime::currentDateTime().time().second()==59)
     {

         businessLogic.CRUD_accept_db->Add(QString::number(sdate.iYear)+"/"+QString::number(sdate.iMonth)
                                               +"/"+QString::number(sdate.iDay),QString::number(acceptcount));
         businessLogic.CRUD_reject_db->Add(QString::number(sdate.iYear)+"/"+QString::number(sdate.iMonth)
                                               +"/"+QString::number(sdate.iDay),QString::number(rejectcount));

    }
}

void MainWindow::CalibrationResultRecived(double maxoval, double minoval)
{
    ui->M_cp_MAX_doubleSpinBox->setValue(maxoval);
    ui->M_cp_MIN_doubleSpinBox->setValue(minoval);
}

void MainWindow::lightscoretestsetting(double score)
{
    ui->label_lightscoresetting->setText(QString::number(score));
}

void MainWindow::increaseDate()
{

}

void MainWindow::get_tabel_db_setting_machine(QMap<QString, QString> *map)
{
    if (!businessLogic.dataMap_setting_machine_db.isEmpty()) {
        ui->SCT_CT_PRM_exposure_SB->setValue(businessLogic.dataMap_setting_camera_db.value("Exposure").toInt());
        ui->SCT_CT_PRM_delay_SB->setValue(businessLogic.dataMap_setting_camera_db.value("Delay").toInt());
        ui->SCT_CT_PRM_XOffset_SB->setValue(businessLogic.dataMap_setting_camera_db.value("XOffset").toInt());
        ui->SCT_CT_PRM_YOffset_SB->setValue(businessLogic.dataMap_setting_camera_db.value("YOffset").toInt());
        ui->SCT_CT_PRM_Width_SB->setValue(businessLogic.dataMap_setting_camera_db.value("Width").toInt());
        ui->SCT_CT_PRM_Height_SB->setValue(businessLogic.dataMap_setting_camera_db.value("Height").toInt());

    } else {
        qDebug() << "The dataMap_setting_machine_db is empty.";
    }
}

void MainWindow::get_tabel_db_setting_camera(QMap<QString, QString> *map)
{
    if (!businessLogic.dataMap_setting_camera_db.isEmpty()) {

        ui->SMT_SWS_MotorSpeed_SP_3->setValue(businessLogic.dataMap_setting_machine_db.value("Star_Wheel_Speed").toInt());
        ui->SMT_FJ_Delay_SB_3->setValue(businessLogic.dataMap_setting_machine_db.value("Feed_Jack_Delay").toInt());
        ui->SMT_FJ_Time_SB_3->setValue(businessLogic.dataMap_setting_machine_db.value("Feed_Jack_Time").toInt());
        ui->SMT_RJ_Delay_SB_3->setValue(businessLogic.dataMap_setting_machine_db.value("Reject_Jack_Delay").toInt());
        ui->SMT_RJ_Time_SB_3->setValue(businessLogic.dataMap_setting_machine_db.value("Reject_Jack_Time").toInt());

    } else {
        qDebug() << "The dataMap_setting_camera_db is empty.";
    }
}

void MainWindow::get_tabel_db_setting_product(QMap<QString, QString> *map)
{
    if (!businessLogic.dataMap_setting_product_db.isEmpty()) {

        QMap<QString, QString>::iterator Iter = businessLogic.dataMap_setting_product_db.begin();
        // qDebug() << " Iter.value():"<< businessLogic.dataMap_setting_product_db.value("Reject_Jack_Delay");
        while(Iter !=businessLogic.dataMap_setting_product_db.end())
        {
            qDebug() << " key:" << Iter.key() << ", value:" << Iter.value();
            ++Iter;
        }

    } else {
        qDebug() << "The dataMap_setting_machine_db is empty.";
    }
    if(!businessLogic.dataMap_setting_product_db.isEmpty())
    {
        ui->SPT_OvalMin_SPB->setValue(businessLogic.dataMap_setting_product_db.value("oval_min").toDouble());
        ui->SPT_OvalMax_SPB->setValue(businessLogic.dataMap_setting_product_db.value("oval_max").toDouble());
        ui->SPT_HeadScore_SPB->setValue(businessLogic.dataMap_setting_product_db.value("head_defect").toDouble());
        ui->SPT_RingScore_SPB->setValue(businessLogic.dataMap_setting_product_db.value("ring_defect").toDouble());
        ui->SPT_Ovalreject_ON_OFF_CHB->setChecked(toBool(businessLogic.dataMap_setting_product_db.value("oval_on_off")));
        ui->SPT_Ringreject_ON_OFF_CHB->setChecked(toBool(businessLogic.dataMap_setting_product_db.value("ring_on_off")));
        ui->SPT_Headreject_ON_OFF_CHB->setChecked(toBool(businessLogic.dataMap_setting_product_db.value("head_on_off")));
    }
    else {
        qDebug() << "The dataMap_setting_product_db is empty.";
    }
}

void MainWindow::CustomPlotDraw()
{
    MaxOval_PLT = new newplotclass;
    MaxOval_PLT->setparameter(580,100,21,ui->SPT_OvalMin_SPB->value()+3,ui->SPT_OvalMin_SPB->value(),ui->SPT_OvalMin_SPB->value()+2,ui->SPT_OvalMin_SPB->value()-2);
    ui->gridLayout_plot_max->addWidget(MaxOval_PLT);
    MinOval_PLT= new newplotclass;
    MinOval_PLT->setparameter(580,100,21,2,(ui->SPT_OvalMax_SPB->value()+1)/2,ui->SPT_OvalMax_SPB->value(),1);
    ui->gridLayout_plot_min->addWidget(MinOval_PLT);
    RingScore_PLT= new newplotclass;
    RingScore_PLT->setparameter(580,100,21,1.1,(1+ui->SPT_RingScore_SPB->value())/2,1,ui->SPT_RingScore_SPB->value());
    ui->gridLayout_plot_RingScore->addWidget(RingScore_PLT);
    HeadScore_PLT= new newplotclass;
    HeadScore_PLT->setparameter(580,100,21,1.1,(1+ui->SPT_HeadScore_SPB->value())/2,1,ui->SPT_HeadScore_SPB->value());
    ui->gridLayout_plot_HeadScore->addWidget(HeadScore_PLT);
    ui->stackedWidget_InspectionPlots_up->setCurrentWidget(ui->stackedWidget_InspectionPlots_up_HeadScore);
    ui->stackedWidget_InspectionPlots_down->setCurrentWidget(ui->stackedWidget_InspectionPlots_Down_RingScore);
}

MainWindow::access_Layer MainWindow::get_Login_Info()
{
    return access_Layer::admin;
}


void MainWindow::on_SCT_CT_SET_pushButton_clicked()
{
    qInfo()<<"Camera SettingUpdated"<<"Width"<<ui->SCT_CT_PRM_Width_SB->text()<<
        "Height"<<ui->SCT_CT_PRM_Height_SB->text()<<
        "YOffset"<<ui->SCT_CT_PRM_YOffset_SB->text()<<
        "XOffset"<<ui->SCT_CT_PRM_XOffset_SB->text()<<
        "Delay"<<ui->SCT_CT_PRM_delay_SB->text()<<
        "Exposure"<<ui->SCT_CT_PRM_exposure_SB->text();
    businessLogic.CRUD_setting_camera_db->Update("Exposure",ui->SCT_CT_PRM_exposure_SB->text());
    businessLogic.CRUD_setting_camera_db->Update("Delay",ui->SCT_CT_PRM_delay_SB->text());
    businessLogic.CRUD_setting_camera_db->Update("XOffset",ui->SCT_CT_PRM_XOffset_SB->text());
    businessLogic.CRUD_setting_camera_db->Update("YOffset",ui->SCT_CT_PRM_YOffset_SB->text());
    businessLogic.CRUD_setting_camera_db->Update("Width",ui->SCT_CT_PRM_Width_SB->text());
    businessLogic.CRUD_setting_camera_db->Update("Height",ui->SCT_CT_PRM_Height_SB->text());

    businessLogic.connectionlayer.Camera_Delay_Setting(ui->SCT_CT_PRM_delay_SB->value());
    businessLogic.connectionlayer.Camera_Exposure_Setting(ui->SCT_CT_PRM_exposure_SB->value());
    if(SCT_CT_GRB_StartStop_PB_IsON_OFF){
        businessLogic.connectionlayer.Camera_ROI_Setting(ui->SCT_CT_PRM_Width_SB->value(),ui->SCT_CT_PRM_Height_SB->value(),ui->SCT_CT_PRM_XOffset_SB->value()
                                                         ,ui->SCT_CT_PRM_YOffset_SB->value());
    }

}




void MainWindow::on_SCT_CT_GRB_StartStop_PB_clicked()
{

    businessLogic.Setting_Save_Image_Flag=ui->SCT_CT_GRB_checkBox->isChecked();
    businessLogic.Setting_count_Image_Save=ui->SCT_CT_GRB_spinbox->value();
    qInfo()<<"CameraGrabberSetting status"<<SCT_CT_GRB_StartStop_PB_IsON_OFF;
    if(SCT_CT_GRB_StartStop_PB_IsON_OFF){
        businessLogic.System_Set_Mode(BusinessLogic::Mode::setting);
        connect(&businessLogic,SIGNAL(send_image(HalconCpp::HImage*)),this,SLOT(Camera_Setting_Image_Recived(HalconCpp::HImage*)));
        businessLogic.connectionlayer.Machie_Run(MachineManager::senario::calibration);
        businessLogic.connectionlayer.Camera_Start_Grabbing_Setting(Connections::CameraGrabMode::Trigger,true);
        SCT_CT_GRB_StartStop_PB_IsON_OFF=false;
                ui->SCT_CT_GRB_StartStop_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Group 407.svg);");
    }
    else{
        businessLogic.System_Set_Mode(BusinessLogic::Mode::systemOff);
        disconnect(&businessLogic,SIGNAL(send_image(HalconCpp::HImage*)),this,SLOT(Camera_Setting_Image_Recived(HalconCpp::HImage*)));
        businessLogic.connectionlayer.Machie_Run(MachineManager::senario::systemOff);
        businessLogic.connectionlayer.Camera_Start_Grabbing_Setting(Connections::CameraGrabMode::Trigger,false);
        SCT_CT_GRB_StartStop_PB_IsON_OFF=true;
        ui->SCT_CT_GRB_StartStop_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-2/Group 406.svg);");
    }


}



void MainWindow::on_SMT_RJ_JogOnOff_PB_3_released()
{
    businessLogic.connectionlayer.JackTest(1,ui->SMT_RJ_Delay_SB_3->text().toDouble(),ui->SMT_RJ_Time_SB_3->text().toDouble()
                                           ,Connections::JacktestMode::Jog,Connections::ONOFF::OFF);
}


void MainWindow::on_maxOval_HeadScore_Swithcer_PB_clicked()
{

    ui->stackedWidget_InspectionPlots_up->setCurrentWidget(ui->stackedWidget_InspectionPlots_up_maxOval);
    ui->maxOval_HeadScore_Swithcer_PB->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Monitor Charts/Group 515.svg);");
    ui->maxOval_HeadScore_Swithcer_PB_2->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Monitor Charts/Group 506.svg);");
}


void MainWindow::on_minOval_RingScore_Swithcer_PB_clicked()
{
    ui->stackedWidget_InspectionPlots_down->setCurrentWidget(ui->stackedWidget_InspectionPlots_Down_minOval);
    ui->minOval_RingScore_Swithcer_PB->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Monitor Charts/Group 517.svg);");
    ui->minOval_RingScore_Swithcer_PB_2->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Monitor Charts/Group 508.svg);");
}


void MainWindow::on_ST_save_pushButton_clicked()
{
    Hlong a1,a2,a3,a4,a5,a6,a7;
    Reject_gallery->imageList.at(Reject_gallery->selsectedItem)->GetImageTime(&a1,&a2,&a3,&a4,&a5,&a6,&a7);
    std::string resultname =std::to_string(a1)+std::to_string(a2)+std::to_string(a3)+std::to_string(a4)
                             +std::to_string(a5)+std::to_string(a6)+std::to_string(a7);
    Reject_gallery->imageList.at(Reject_gallery->selsectedItem)->WriteImage("tiff",0,resultname.c_str());
}


void MainWindow::on_M_sp_reset_pushButton_clicked()
{
    acceptcount=1;
    rejectcount=1;
    statistic->series->slices().at(0)->setValue(acceptcount);
    statistic->series->slices().at(1)->setValue(rejectcount);
    ui->Accept_Count_LB->setText(QString::number(acceptcount));
    ui->Reject_Count_LB->setText(QString::number(rejectcount));
}




void MainWindow::on_M_parameter_keyboard_PB_clicked()
{
    keyboard->start("FreeVK.exe");
}


void MainWindow::on_SUT_parameter_keyboard_PB_clicked()
{
    keyboard->start("FreeVK.exe");
}


void MainWindow::on_SPT_parameter_keyboard_PB_clicked()
{
   keyboard->start("FreeVK.exe");
}


void MainWindow::on_SCT_CT_parameter_keyboard_PB_clicked()
{
    keyboard->start("FreeVK.exe");
}


void MainWindow::on_SCT_Machine_parameter_keyboard_PB_clicked()
{
    keyboard->start("FreeVK.exe");
}


void MainWindow::on_M_start_stop_pushButton_clicked()
{
    if(start_stop_pushButton_Flag)
    {
        ui->M_start_stop_pushButton->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group 220.svg);");

    connect(&businessLogic,SIGNAL(send_image(HalconCpp::HImage*)),this,SLOT(recived_image(HalconCpp::HImage*)));
    businessLogic.System_Set_Mode(BusinessLogic::Mode::Inspection);
    qInfo()<<"inspection start";


    ui->Setting_PB->setVisible(false);
    ui->Statistic_PB->setVisible(false);

    start_stop_pushButton_Flag=false;
    }
    else
    {
        ui->M_start_stop_pushButton->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 384.svg);");
     qInfo()<<"inspection stop";
    disconnect(&businessLogic,SIGNAL(send_image(HalconCpp::HImage*)),this,SLOT(recived_image(HalconCpp::HImage*)));
    businessLogic.System_Set_Mode(BusinessLogic::Mode::systemOff);


    ui->Setting_PB->setVisible(true);
    ui->Statistic_PB->setVisible(true);
        start_stop_pushButton_Flag=true;
    }
}


void MainWindow::on_M_cp_calibration_on_off_pushButton_clicked()
{
    Set_page(pages_::Callibration);
    ui->stackedWidge_->setCurrentWidget(ui->Callibration);
    // if(calibration_on_off_pushButton)
    // {
    //     ui->M_cp_calibration_on_off_pushButton->setStyleSheet("");
    // // connect(&businessLogic,SIGNAL(send_image(HalconCpp::HImage*)),this,SLOT(recived_image(HalconCpp::HImage*)));
    // // businessLogic.System_Set_Mode(BusinessLogic::Mode::calibration);
    //     calibration_on_off_pushButton=false;
    // }
    // else
    // {
    //      ui->M_cp_calibration_on_off_pushButton->setStyleSheet("");
    //     // disconnect(&businessLogic,SIGNAL(send_image(HalconCpp::HImage*)),this,SLOT(recived_image(HalconCpp::HImage*)));
    //     // businessLogic.System_Set_Mode(BusinessLogic::Mode::systemOff);
    //     calibration_on_off_pushButton=true;
    // }



}


void MainWindow::on_M_cp__statistics_pushButton_clicked()
{
    Set_page(pages_::Statistic);
    ui->stackedWidge_->setCurrentWidget(ui->Statistics);
    // if(statistics_pushButton)
    // {
    //     ui->M_cp__statistics_pushButton->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-1 edited/Group 382.png);");
    //     statistics_pushButton=false;
    // }
    // else
    // {
    //     ui->M_cp__statistics_pushButton->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 1-2/Group 386.svg);");
    //     statistics_pushButton=true;
    // }

}

void MainWindow::on_M_cp_status_pushButton_clicked()
{
    Set_page(pages_::Status);
    ui->stackedWidge_->setCurrentWidget(ui->Status);
}

void MainWindow::on_ST_report_pushButton_clicked()
{
    businessLogic.Report_db();
    QFileDialog dialog;
    QString saveFileName = dialog.getSaveFileName(nullptr,"Save as xlsx","","xlsx Files (*.xlsx)");
    QXlsx::Document xlsx;
    QXlsx::Format format1;
    QXlsx::Format format2;
    QXlsx::Format format3;
    QXlsx::Format format4;
    if((!saveFileName.isEmpty())){
        format1.setPatternBackgroundColor(QColor(Qt::red));
        format1.setFontSize(12);
        format1.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
        format1.setBorderStyle(QXlsx::Format::BorderThin);

        format2.setPatternBackgroundColor(QColor(Qt::green));
        format2.setFontSize(12);
        format2.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
        format2.setBorderStyle(QXlsx::Format::BorderThin);

        format3.setFontSize(15);
        format3.setBorderStyle(QXlsx::Format::BorderThin);
        format3.setPatternBackgroundColor(QColor(252,185,51));
        format4.setFontSize(15);
        format4.setBorderStyle(QXlsx::Format::BorderThin);
        xlsx.mergeCells("A1:C1");
        xlsx.setRowHeight(1,40);
        xlsx.setColumnWidth(1,25);
        xlsx.setColumnWidth(2,30);
        xlsx.setColumnWidth(3,30);
        QImage image (":/Tivanex - App Ui - Preform/TivanEX logo.png");
        QImage resizedImage = image.scaled(730, 140, Qt::KeepAspectRatio);
        xlsx.insertImage(0,1,resizedImage);
        xlsx.write(3,1,"Product : " ,format3);
        xlsx.write(4,1,"From : " ,format3);
        xlsx.write(5,1,"To : " ,format3);

        xlsx.write(3,2,"Preform",format3);
        xlsx.write(4,2,NewDate_From,format3);
        xlsx.write(5,2,NewDate_To,format3);

        xlsx.write(3,3,"",format3);
        xlsx.write(4,3,"",format3);
        xlsx.write(5,3,"",format3);

        xlsx.write(7,1,"FROM",format4);

        if (!businessLogic.dataMap_accept_db.isEmpty()) {

                QMap<QString, QString>::iterator Iter = businessLogic.dataMap_accept_db.begin();
                qDebug() << NewDate_From << businessLogic.dataMap_accept_db.value(NewDate_From);
                xlsx.write(7,2,businessLogic.dataMap_accept_db.value(NewDate_From),format2);
        }
                // while(Iter !=dataMap_setting_machine_db.end())
                // {
                //     qDebug() << " key:" << Iter.key() << ", value:" << Iter.value();
                //     ++Iter;
                // }
        // xlsx.write(7,2,q.value("sum (cl_accepted)"),format2);
        // xlsx.write(7,3,q.value("sum (cl_rejected)"),format1);

        // xlsx.write(8,1,"FL1",format4);

        // xlsx.write(8,2,q.value("sum (fl1_accepted)"),format2);
        // xlsx.write(8,3,q.value("sum (fl1_rejected)"),format1);

        // xlsx.write(9,1,"FL2",format4);

        // xlsx.write(9,2,q.value("sum (fl2_accepted)"),format2);
        // xlsx.write(9,3,q.value("sum (fl2_rejected)"),format1);
        xlsx.saveAs(saveFileName);
}

}
void MainWindow::on_Machine_Setting_PB_clicked()
{
    qInfo()<<"Machine setting Page";
    ui->Machine_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - "
                                          "App Ui 04 - Page 2-1/Group 389.svg);background-color: transparent;");
    ui->Camera_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - "
                                         "Preform/Tivanex - App Ui 04 - Page 2-1/Group 390.svg);background-color: transparent;");
    ui->Product_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex -"
                                          " App Ui 04 - Page 2-1/Group 391.svg);background-color: transparent;");
    ui->User_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group"
                                       " 392.svg);background-color: transparent;");
    ui->SettingStackWidget->setCurrentWidget(ui->MachineSettingPage);
}


void MainWindow::on_Camera_Setting_PB_clicked()
{
    qInfo()<<"Camera setting Page";
    ui->SettingStackWidget->setCurrentWidget(ui->CameraSettingPage);
    ui->Machine_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 403.svg);"
                                          "background-color: transparent;");
    ui->Camera_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 402.svg);"
                                         "background-color: transparent;");
    ui->Product_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex -"
                                          " App Ui 04 - Page 2-1/Group 391.svg);background-color: transparent;");
    ui->User_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group"
                                       " 392.svg);background-color: transparent;");
}


void MainWindow::on_Product_Setting_PB_clicked()
{
    qInfo()<<"Product setting Page";
    ui->SettingStackWidget->setCurrentWidget(ui->ProductSettingPage);
    ui->Machine_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 403.svg);"
                                          "background-color: transparent;");
    ui->Camera_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - "
                                         "Preform/Tivanex - App Ui 04 - Page 2-1/Group 390.svg);background-color: transparent;");
        ui->Product_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-3/Tivanex - App Ui 04 - Page 2-3/Group 412.svg)"
                                          ";background-color: transparent;");
    ui->User_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-1/Group"
                                       " 392.svg);background-color: transparent;");
}


void MainWindow::on_User_Setting_PB_clicked()
{
    qInfo()<<"User setting Page";
    ui->SettingStackWidget->setCurrentWidget(ui->UserSettingPage);
    ui->Machine_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-2-1/Group 403.svg);"
                                          "background-color: transparent;");
    ui->Camera_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - "
                                         "Preform/Tivanex - App Ui 04 - Page 2-1/Group 390.svg);background-color: transparent;");
    ui->Product_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex -"
                                          " App Ui 04 - Page 2-1/Group 391.svg);background-color: transparent;");
      ui->User_Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 2-4/Group 417.svg)"
                                       ";background-color: transparent;");

}



void MainWindow::on_Monitor_PB_clicked()
{
    qInfo()<<"Monitor Page";
    ui->Software_StackWidget->setCurrentWidget(ui->MonitorPage);
    ui->Monitor_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex"
                                  " - App Ui 04 - Page 1-2/Manitor - Big - ON.svg);");
    ui->Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex "
                                  "- App Ui 04 - Page 1-2/Setting - Small - OFF.svg);");
    ui->Statistic_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex"
                                    " - App Ui 04 - Page 1-2/Statisic - Small - OFF.svg);");
    ui->Help_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex "
                               "- App Ui 04 - Page 1-2/Help - Small - OFF.svg);");
}


void MainWindow::on_Setting_PB_clicked()
{
    qInfo()<<"Setting Page";
    ui->Software_StackWidget->setCurrentWidget(ui->SettingPage);
    ui->Monitor_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex"
                                  " - App Ui 04 - Page 1-2/Manitor - Small - OFF.svg);");
    ui->Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex "
                                  "- App Ui 04 - Page 1-2/Setting - Big - ON.svg);");
    ui->Statistic_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex"
                                    " - App Ui 04 - Page 1-2/Statisic - Small - OFF.svg);");
    ui->Help_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex "
                               "- App Ui 04 - Page 1-2/Help - Small - OFF.svg);");
}


void MainWindow::on_Statistic_PB_clicked()
{
    qInfo()<<"Statistic Page";
    ui->Software_StackWidget->setCurrentWidget(ui->StatisticPage);
    ui->Monitor_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex"
                                  " - App Ui 04 - Page 1-2/Manitor - Small - OFF.svg);");
    ui->Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex "
                                  "- App Ui 04 - Page 1-2/Setting - Small - OFF.svg);");
    ui->Statistic_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex"
                                    " - App Ui 04 - Page 1-2/Statisic - Big - ON.svg);");
    ui->Help_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex "
                               "- App Ui 04 - Page 1-2/Help - Small - OFF.svg);");
}


void MainWindow::on_Help_PB_clicked()
{
    qInfo()<<"Help Page";
    ui->Software_StackWidget->setCurrentWidget(ui->HelpPage);
    ui->Monitor_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex"
                                  " - App Ui 04 - Page 1-2/Manitor - Small - OFF.svg);");
    ui->Setting_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex "
                                  "- App Ui 04 - Page 1-2/Setting - Small - OFF.svg);");
    ui->Statistic_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex"
                                    " - App Ui 04 - Page 1-2/Statisic - Small - OFF.svg);");
    ui->Help_PB->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex "
                               "- App Ui 04 - Page 1-2/Help - Big - ON.svg);");
}


void MainWindow::on_M_switch_user_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->LoginPage);
}


void MainWindow::on_M_power_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->PowerPage);
}


void MainWindow::on_LoginPage_keyboard_PB_clicked()
{
    keyboard->start("FreeVK.exe");

}


void MainWindow:: on_Login_PB_clicked()
{
    if(!businessLogic.dataMap_setting_user_db.contains(ui->Login_UserName_LE->text()))
    {
        QMessageBox::warning(nullptr, "Input Error", "Username does not exist.");
    }else{
        if (businessLogic.dataMap_setting_user_db.value(ui->Login_UserName_LE->text()) != ui->Login_Password_LE->text()) {
            QMessageBox::warning(nullptr, "Login Failed", "Invalid password. Please try again.");
        }else{

            if(businessLogic.dataMap_setting_user_role_db.value(ui->Login_UserName_LE->text())=="Admin"){
                ui->SUT_ChangeUser_AccessLevel_LB->setText("admin");
                Set_Access(access_Layer::admin);
                user_current=ui->Login_UserName_LE->text();
            }else{
                ui->SUT_ChangeUser_AccessLevel_LB->setText("user");
                Set_Access(access_Layer::normaluser);
                user_current=ui->Login_UserName_LE->text();
            }
            ui->stackedWidget->setCurrentWidget(ui->SoftwarePages);
            qInfo()<<"User:"<<ui->Login_UserName_LE->text()<<" is responsible";
        }
    }





}


void MainWindow::on_shotDown_PB_clicked()
{
    businessLogic.CRUD_accept_db->Add(QString::number(sdate.iYear)+"/"+QString::number(sdate.iMonth)
                                      +"/"+QString::number(sdate.iDay),QString::number(acceptcount));
    businessLogic.CRUD_reject_db->Add(QString::number(sdate.iYear)+"/"+QString::number(sdate.iMonth)
                                          +"/"+QString::number(sdate.iDay),QString::number(rejectcount));
    businessLogic.System_Set_Mode(BusinessLogic::Mode::systemOff);
    QString command = "shutdown /s /t 0";
    QProcess process;
    process.startDetached("cmd.exe", {"/c", command});
}


void MainWindow::on_SUT_ChangeUser_SET_PB_clicked()
{

        if (!isValidPassword(ui->SUT_ChangeUser_password_LE->text())) {
            QMessageBox::warning(nullptr, "Change Failed", "Invalid password. Please try again.");
        }else {
            if (ui->SUT_ChangeUser_password_LE->text() != ui->SUT_ChangeUser_passwordValid_LE_2->text()) {
                QMessageBox::warning(nullptr, "Change Failed", "Validation Erorr. Please try again.");
            }
            else{
            businessLogic.CRUD_setting_user_db->Update(user_current,ui->SUT_ChangeUser_password_LE->text());
                ui->SUT_ChangeUser_password_LE->setText("");
            ui->SUT_ChangeUser_passwordValid_LE_2->setText("");
            }
        }
}


void MainWindow::on_Reset_PB_clicked()
{
    businessLogic.System_Set_Mode(BusinessLogic::Mode::systemOff);
    QString command = "shutdown /r /t 0";
    QProcess process;
    process.startDetached("cmd.exe", {"/c", command});
}


void MainWindow::on_back_to_main_PB_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->SoftwarePages);
}



void MainWindow::on_back_to_deckstop_PB_clicked()
{
    setWindowState(Qt::WindowMinimized);
}


void MainWindow::on_plcconnection_CHB_checkStateChanged(const Qt::CheckState &arg1)
{
    qInfo()<<"plc Connection status:"<<arg1;
    if(arg1==Qt::Checked)
    {
        ui->SMT_SWS_MotorStartStop_PB_3->setVisible(true);
        ui->SMT_RJ_StartStop_PB_3->setVisible(true);
        ui->SMT_RJ_JogOnOff_PB_3->setVisible(true);
        ui->SMT_FJ_JogOnOff_PB_3->setVisible(true);
        ui->SMT_FJ_StartStop_PB_3->setVisible(true);

        ui->M_start_stop_pushButton->setVisible(true);
        ui->Statistic_PB->setVisible(true);

        businessLogic.PlcConnection();
    }
    else
    {
        ui->SMT_SWS_MotorStartStop_PB_3->setVisible(false);
         ui->SMT_RJ_StartStop_PB_3->setVisible(false);
        ui->SMT_RJ_JogOnOff_PB_3->setVisible(false);
        ui->SMT_FJ_JogOnOff_PB_3->setVisible(false);
        ui->SMT_FJ_StartStop_PB_3->setVisible(false);

        ui->M_start_stop_pushButton->setVisible(false);
        ui->Statistic_PB->setVisible(false);

        businessLogic.PlcDisconnection();
    }
}


void MainWindow::on_cameraconnection_CHB_checkStateChanged(const Qt::CheckState &arg1)
{
    qInfo()<<"camera Connection status:"<<arg1;
    if(arg1==Qt::Checked)
    {
        ui->M_start_stop_pushButton->setVisible(true);
        ui->Statistic_PB->setVisible(true);
        ui->SCT_CT_GRB_StartStop_PB->setVisible(true);
        ui->SCT_CT_SET_pushButton->setVisible(true);
        businessLogic.CameraReconnection();
    }
    else

    {
        ui->M_start_stop_pushButton->setVisible(false);
        ui->Statistic_PB->setVisible(false);
        ui->SCT_CT_GRB_StartStop_PB->setVisible(false);
        ui->SCT_CT_SET_pushButton->setVisible(false);
            businessLogic.CameraDisconnection();
    }

}


void MainWindow::on_ST_keyboard_pushButton_clicked()
{
    keyboard->start("FreeVK.exe");
}


void MainWindow::on_maxOval_HeadScore_Swithcer_PB_2_clicked()
{
    ui->stackedWidget_InspectionPlots_up->setCurrentWidget(ui->stackedWidget_InspectionPlots_up_HeadScore);
    ui->maxOval_HeadScore_Swithcer_PB->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Monitor Charts/Group 514.svg);");
    ui->maxOval_HeadScore_Swithcer_PB_2->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Monitor Charts/Group 507.svg);");

}


void MainWindow::on_minOval_RingScore_Swithcer_PB_2_clicked()
{
    ui->stackedWidget_InspectionPlots_down->setCurrentWidget(ui->stackedWidget_InspectionPlots_Down_RingScore);
    ui->minOval_RingScore_Swithcer_PB->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Monitor Charts/Group 516.svg);");
    ui->minOval_RingScore_Swithcer_PB_2->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Monitor Charts/Group 509.svg);");

}


void MainWindow::on_SCT_Sample_Image_pushButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "انتخاب تصویر",
        QDir::homePath(),
        "Images (*.png *.jpg *.jpeg *.bmp *.gif *.tif)"  );

    if (filePath.isEmpty()) {
        QMessageBox::information(this, "اطلاع", "فایلی انتخاب نشد!");
        return;
    }

    QPixmap pixmap(filePath);

    if (pixmap.isNull()) {
        QMessageBox::critical(this, "خطا", "بارگذاری تصویر با مشکل مواجه شد!");
        return;
    }

    ui->SCT_CP_ImagePreviewWindow_label->setPixmap(pixmap.scaled(
        ui->SCT_CP_ImagePreviewWindow_label->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        ));
    QFile file("Image_Sample.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << filePath;
        file.close();
    }
}
void MainWindow::loadImageOnStartup()
{
    QFile file("Image_Sample.txt");
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString savedFilePath = in.readLine();
        file.close();
        QPixmap pixmap(savedFilePath);
        if (!pixmap.isNull()) {
            ui->SCT_CP_ImagePreviewWindow_label->setPixmap(pixmap.scaled(
                ui->SCT_CP_ImagePreviewWindow_label->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
                ));
        }
    }
}
