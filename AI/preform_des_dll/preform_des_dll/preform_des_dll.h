#ifndef PREFORM_DES_DLL_H
#define PREFORM_DES_DLL_H

#include "preform_des_dll_global.h"
#include "HalconCpp.h"
#include "HDevThread.h"

class PREFORM_DES_DLL_EXPORT Preform_des_dll
{
public:

    Preform_des_dll(HalconCpp::HImage Image, double max_oval = 70, double min_oval = 40 , double limit_ring = 90, double limit_head = 90
            , double pixel_way1 = 1, double pixel_way2 = 1, int threshold = 60);


    bool get_flag_ring();
    bool get_flag_head();
    bool get_flag_oval();
    double get_max_oval();
    double get_min_oval();
    double get_score_ring();
    double get_score_head();
    HalconCpp::HImage get_image();

private:

    bool flag_ring, flag_head, flag_oval;
    HalconCpp::HTuple score_ring, score_head;
    HalconCpp::HImage image;
    double max_ov, min_ov, score;

};

#endif // PREFORM_DES_DLL_H
