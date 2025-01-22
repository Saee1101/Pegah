#include "head_defect.h"
#include "HalconCpp.h"
#include "HDevThread.h"

using namespace HalconCpp;

head_defect::head_defect(HalconCpp::HObject ho_head, double sigma)
{

        //get: head
        //return: head_defect

    // Local iconic variables
    HObject  ho_Circle, ho_RegionDifference1;
    HObject  ho_RegionDifference2, ho_head_defect;

    // Local control variables
    HTuple  hv_Row1, hv_Column1, hv_Radius1, hv_outmax1, hv_outmin1;
    try {

        SmallestCircle(ho_head, &hv_Row1, &hv_Column1, &hv_Radius1);
        GenCircle(&ho_Circle, hv_Row1, hv_Column1, hv_Radius1);
        Difference(ho_Circle, ho_head, &ho_RegionDifference1);
        InnerCircle(ho_RegionDifference1, &hv_Row1, &hv_Column1, &hv_Radius1);
        GenCircle(&ho_Circle, hv_Row1, hv_Column1, hv_Radius1);
        Difference(ho_RegionDifference1, ho_Circle, &ho_RegionDifference2);
        OpeningCircle(ho_RegionDifference2, &ho_head_defect, sigma);

    } catch (...) {
        GenEmptyObj(&ho_head_defect);
    }

    head_defects = ho_head_defect;
}
