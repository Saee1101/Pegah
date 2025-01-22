#ifndef AVAILABLE_CAMERAS_H
#define AVAILABLE_CAMERAS_H
#include "HalconCpp.h"
#include <iostream>
#include <vector>
#include <QString>
#include <QDebug>
using namespace HalconCpp;

#include <QObject>

class Available_Cameras : public QObject
{
    Q_OBJECT
public:
    explicit Available_Cameras(QObject *parent = nullptr);
    void cam_name_sender(QStringList* camlist);
    QString camname;


signals:
    void Send_Camera_Name(QString name);

};

#endif // AVAILABLE_CAMERAS_H
