#include "post_pro.h"
#include "HalconCpp.h"
#include "HDevThread.h"

using namespace HalconCpp;


post_pro::post_pro(HalconCpp::HImage Image, HalconCpp::HObject ho_oval, HalconCpp::HObject ho_ring_defect, HalconCpp::HObject ho_head_defect)
{

            //get: Image, oval, ring_defect, head_defect
            //return: Image


        // Local iconic variables
        HObject  ho_Image(Image), ho_Region, ho_Circle, ho_ObjectSelected;
        HObject  ho_RegionBorder;
        HObject  ho_RegionBorder1, ho_RegionBorder2;


        // Local control variables
        HTuple  hv_WindowHandle;
        try {


    SetWindowAttr("background_color","black");
    OpenWindow(0,0,512,512,0,"buffer","",&hv_WindowHandle);

    Boundary(ho_oval, &ho_RegionBorder, "inner");
    Boundary(ho_ring_defect, &ho_RegionBorder1, "inner");
    Boundary(ho_head_defect, &ho_RegionBorder2, "inner");


    DilationCircle(ho_RegionBorder,&ho_RegionBorder, 5.5);
    DilationCircle(ho_RegionBorder1,&ho_RegionBorder1, 5.5);
    DilationCircle(ho_RegionBorder2,&ho_RegionBorder2, 5.5);

    DispObj(ho_Image,hv_WindowHandle);
    SetColor(hv_WindowHandle, "yellow");
    DispObj(ho_RegionBorder, hv_WindowHandle);
    SetColor(hv_WindowHandle, "green");
    DispObj(ho_RegionBorder1, hv_WindowHandle);
    SetColor(hv_WindowHandle, "red");
    DispObj(ho_RegionBorder2, hv_WindowHandle);


    DumpWindowImage(&ho_Image, hv_WindowHandle);
    CloseWindow(hv_WindowHandle);


        } catch (...) {
            GenEmptyObj(&ho_Image);
        }

        HImage output_image1(ho_Image);
    output_image = output_image1;

}
