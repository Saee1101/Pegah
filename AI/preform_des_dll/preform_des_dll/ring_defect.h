#ifndef RING_DEFECT_H
#define RING_DEFECT_H


#include <QObject>
#include "HalconCpp.h"
#include "HDevThread.h"

class ring_defect
{

public:

    ring_defect(HalconCpp::HObject ring, HalconCpp::HTuple Row,HalconCpp::HTuple Column,HalconCpp::HTuple Radius,double sigma = 10.5);

    HalconCpp::HObject ring_defects;
};

#endif // RING_DEFECT_H
