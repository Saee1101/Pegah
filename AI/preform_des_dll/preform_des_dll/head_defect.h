#ifndef HEAD_DEFECT_H
#define HEAD_DEFECT_H

#include "HalconCpp.h"
#include "HDevThread.h"



class head_defect
{
public:

    head_defect(HalconCpp::HObject head, double sigma = 10.5);

    HalconCpp::HObject head_defects;

};

#endif // HEAD_DEFECT_H
