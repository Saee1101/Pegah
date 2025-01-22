#include "ring_defect.h"
#include "HalconCpp.h"
#include "HDevThread.h"

using namespace HalconCpp;

ring_defect::ring_defect(HalconCpp::HObject ho_ring, HTuple hv_Row,HTuple hv_Column,HTuple hv_Radius,double sigma)
{

            //get: ring, Row, Column, Radius
            //return: ring_defect


        // Local iconic variables
        HObject  ho_Circle;
        HObject  ho_RegionDifference;
        HObject  ho_ring_defect;

        // Local control variables

        try {

    GenCircle(&ho_Circle, hv_Row, hv_Column, hv_Radius);
    Difference(ho_Circle, ho_ring, &ho_RegionDifference);
    InnerCircle(ho_RegionDifference, &hv_Row, &hv_Column, &hv_Radius);
    GenCircle(&ho_Circle, hv_Row, hv_Column, hv_Radius);
    Difference(ho_RegionDifference, ho_Circle, &ho_RegionDifference);
    OpeningCircle(ho_RegionDifference, &ho_ring_defect, sigma);

        } catch (...) {

            GenEmptyObj(&ho_ring_defect);
        }
    ring_defects = ho_ring_defect;
}
