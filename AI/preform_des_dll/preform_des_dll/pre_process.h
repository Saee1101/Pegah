#ifndef PRE_PROCESS_H
#define PRE_PROCESS_H


#include <QObject>
#include "HalconCpp.h"
#include "HDevThread.h"

class pre_process
{

public:

    explicit pre_process(HalconCpp::HImage input_image, int threshold = 60, double sigma = 3.5);
    HalconCpp::HObject head,  ring,  oval;
    HalconCpp::HTuple Row, Column, Radius;

signals:

    // Add signals here if needed
};

#endif // PRE_PROCESS_H
