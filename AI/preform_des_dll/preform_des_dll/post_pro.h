#ifndef POST_PRO_H
#define POST_PRO_H


#include "HalconCpp.h"
#include "HDevThread.h"


class post_pro

{

public:

    post_pro(HalconCpp::HImage Image, HalconCpp::HObject oval, HalconCpp::HObject ring_defect, HalconCpp::HObject head_defect);

    HalconCpp::HImage output_image;
};

#endif // POST_PRO_H
