#include "oval_measurement.h"

#include "HalconCpp.h"
#include "HDevThread.h"

#include <cmath>

using namespace HalconCpp;

oval_measurement::oval_measurement(HalconCpp::HObject ho_oval, int sample, double hv_pix1 , double hv_pix2)
{

            //get: oval, pix1, pix2
            //return: outmax1, outmin1, outmax2, outmin2


        // Local iconic variables
        HObject  ho_measure_line;

        // Local control variables
        HTuple  hv_i;
        HTuple  hv_outmax1, hv_outmin1;
        HTuple  hv_outmax2, hv_outmin2, hv_Value, hv_Value1, hv_size;
        HTuple  hv_max_diameter;

        try {


    RegionFeatures(ho_oval, "ra", &hv_outmax1);
    RegionFeatures(ho_oval, "rb", &hv_outmin1);

    hv_outmax1 = hv_outmax1*2;
    hv_outmin1 = hv_outmin1*2;

    if (0 != (hv_outmax1==HTuple())){
      hv_outmax1 = 0;
      hv_outmin1 = 0;
      hv_outmax2 = 0;
      hv_outmin2 = 0;

    }
    else {
      RegionFeatures(ho_oval, "row", &hv_Value);
      RegionFeatures(ho_oval, "column", &hv_Value1);

      hv_size = HTuple();
      {

      HTuple end_val75 = 179;
      HTuple step_val75 = 180/sample;
      for (hv_i=0; hv_i.Continue(end_val75, step_val75); hv_i += step_val75) {
        GenRectangle2(&ho_measure_line, hv_Value, hv_Value1, hv_i.TupleRad(), 1000,
            0);
        Intersection(ho_measure_line, ho_oval, &ho_measure_line);
        RegionFeatures(ho_measure_line, "max_diameter", &hv_max_diameter);
        hv_size = hv_size.TupleConcat(hv_max_diameter);
      }

      }
      hv_outmax2 = hv_size.TupleMax();
      hv_outmin2 = hv_size.TupleMin();
      hv_size = HTuple();

      outmax1 = hv_outmax1*hv_pix1;
      outmin1 = hv_outmin1*hv_pix2;
      outmax2 = hv_outmax2*hv_pix1;
      outmin2 = hv_outmin2*hv_pix2;

    }

        } catch (...) {

            outmax1 = 0;
            outmin1 = 0;
            outmax2 = 0;
            outmin2 = 0;
        }

        outmax1 = std::round(outmax1 * 10000) / 10000;
        outmin1 = std::round(outmin1 * 10000) / 10000;
        outmax2 = std::round(outmax2 * 10000) / 10000;
        outmin2 = std::round(outmin2 * 10000) / 10000;
}
