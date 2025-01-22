#include "pre_process.h"
#include "HalconCpp.h"
#include "HDevThread.h"

using namespace HalconCpp;

pre_process::pre_process(HalconCpp::HImage input_image, int threshoold, double sigma)
{

            //pre pro
            //get: image
            //return: Row, Column, Radius
            //return: head, ring, oval


        // Local iconic variables
        HObject  ho_Image(input_image), ho_Region, ho_Circle, ho_ObjectSelected;
        HObject  ho_head, ho_ring, ho_headFillUp, ho_oval;

        // Local control variables
        HTuple  hv_Row, hv_Column, hv_Radius, hv_distanc;
        HTuple  hv_Number, hv_i, hv_MinDistance, hv_junk, hv_mea;

        try {


    Threshold(ho_Image, &ho_Region, threshoold, 255);
    OpeningCircle(ho_Region, &ho_Region, sigma);
    SmallestCircle(ho_Region, &hv_Row, &hv_Column, &hv_Radius);
    GenCircle(&ho_Circle, hv_Row, hv_Column, 9.5);
    Connection(ho_Region, &ho_Region);
    SelectShape(ho_Region, &ho_Region, "area", "and", 10000, "max");
    hv_distanc = HTuple();
    CountObj(ho_Region, &hv_Number);
    {
    HTuple end_val16 = hv_Number;
    HTuple step_val16 = 1;
    for (hv_i=1; hv_i.Continue(end_val16, step_val16); hv_i += step_val16)
    {
      SelectObj(ho_Region, &ho_ObjectSelected, hv_i);
      DistanceRrMin(ho_Circle, ho_ObjectSelected, &hv_MinDistance, &hv_junk, &hv_junk,
          &hv_junk, &hv_junk);
      hv_distanc = hv_distanc.TupleConcat(hv_MinDistance);
    }
    }


    //trying to get a limit for choosing which one is ring and witch is head
    hv_mea = ((hv_distanc.TupleMax())+(hv_distanc.TupleMin()))/2;
    hv_distanc = hv_distanc.TupleLessElem(hv_mea);
    SelectObj(ho_Region, &ho_head, (hv_distanc.TupleFind(1))+1);
    Union1(ho_head, &ho_head);
    SelectObj(ho_Region, &ho_ring, (hv_distanc.TupleFind(0))+1);
    Union1(ho_ring, &ho_ring);


    //get the region for oval measurement
    FillUp(ho_head, &ho_headFillUp);
    Difference(ho_headFillUp, ho_head, &ho_oval);
    Connection(ho_oval, &ho_oval);
    SelectShapeStd(ho_oval, &ho_oval, "max_area", 99);

        } catch (...) {
            GenEmptyObj(&ho_head);
            GenEmptyObj(&ho_ring);
            GenEmptyObj(&ho_oval);
            hv_Row = 0;
            hv_Column = 0;
            hv_Radius = 0;
        }

    head = ho_head;
    ring = ho_ring;
    oval = ho_oval;
    Row = hv_Row;
    Column = hv_Column;
    Radius = hv_Radius;
}
