#include "available_cameras.h"
using namespace HalconCpp;


Available_Cameras::Available_Cameras(QObject *parent) : QObject(parent){
}

void Available_Cameras::cam_name_sender(QStringList* camlist)
{

    camlist->clear();
    HTuple availableDevices;
    HInfo list;

    list.InfoFramegrabber("GigEVision2", "device", &availableDevices);

    if (availableDevices.Length() == 0) {
        std::cout << "No camera devices found." << std::endl;
    } else {
        std::cout << "Connected camera devices:" << std::endl;
        for (int i = 0; i < availableDevices.Length(); i++) {
            std::string stdString = availableDevices[i].S().Text();
            QString s =QString::fromStdString(stdString);
            QStringList stringList = s.split("|");
            QString result =stringList.at(1);
            result .replace("device:", "");
            QString name = result.remove(" ");
            std::string stdString1 = availableDevices[i].S().Text();
            QString s1 =QString::fromStdString(stdString);
            QStringList stringList1 = s1.split("|");
            QString result1 =stringList.at(2);
            QString result2 = result1 .replace("unique_name:", "");
            QStringList Brand = result2.split("_");
            QString BrandName = Brand.at(1);
            if (BrandName == "TheImagingSourceEuropeGmbH")
                BrandName = "IMS";
            QString Final = name + "_" + BrandName;
            camlist->append(Final);

        }
    }
}
