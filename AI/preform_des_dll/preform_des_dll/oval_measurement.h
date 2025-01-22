#ifndef OVAL_MEASUREMENT_H
#define OVAL_MEASUREMENT_H

#include "HalconCpp.h"
#include "HDevThread.h"



class oval_measurement
{
public:

    oval_measurement(HalconCpp::HObject oval,int sample = 10, double pix_max = 1, double pix_min = 1);

    double outmax1, outmin1, outmax2, outmin2 ;
};

#endif // OVAL_MEASUREMENT_H
