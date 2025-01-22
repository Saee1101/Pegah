#include "preform_light.h"

#include <cmath>

#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>


using namespace HalconCpp;

Preform_light::Preform_light(const char *path)
{
    get_json_path(path);
}

void Preform_light::get_json_path(const char *path)
{
    const char* json_path1(path);
    json_path = json_path1;
}

void Preform_light::process(HalconCpp::HImage ho_Image, double sigma, int threshold)
{


    // Local iconic variables
    HObject  ho_Region;

    // Local control variables
    HTuple  hv_Row, hv_Column, hv_Radius, hv_junk;
    HTuple  hv_RelativeHisto, hv_ideal_light, hv_score;

    try {
        // Define the path to your JSON file
        QString filePath = json_path;

        // Open the JSON file
        QFile File(filePath);
        if (!File.open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open the file!";
        }
        QByteArray Bytes = File.readAll();

        QJsonParseError JsonError;
        QJsonDocument Document = QJsonDocument::fromJson(Bytes, &JsonError);
        if (JsonError.error != QJsonParseError::NoError){
            qDebug() << "error" << JsonError.errorString();
        }

        QJsonObject obj = Document.object();



        Threshold(ho_Image, &ho_Region, obj.value("threshold").toInt(), 255);
        FillUp(ho_Region, &ho_Region);
        Connection(ho_Region, &ho_Region);
        SelectShape(ho_Region, &ho_Region, "area", "and", 5000, "max");
        Union1(ho_Region, &ho_Region);
        SmallestCircle(ho_Region, &hv_Row, &hv_Column, &hv_Radius);
        GenCircle(&ho_Region, hv_Row, hv_Column, hv_Radius);

        GrayHisto(ho_Region, ho_Image, &hv_junk, &hv_RelativeHisto);


        hv_ideal_light.Clear();
        for (int i = 0;i<256;i++){
            QString str = QString::number(i);
            hv_ideal_light[i] = obj.value(str).toDouble();
        }



        hv_score = obj.value("sigma").toDouble() * ( 1 / ( ( ( hv_RelativeHisto - hv_ideal_light ).TupleAbs() ).TupleSum() ) );

        if (0 != (hv_score>1)){hv_score = 1;}

        score = hv_score.D();
        if (std::isnan(score)){score= 0;}

    } catch (...) {
        score = 0;
    }
}

