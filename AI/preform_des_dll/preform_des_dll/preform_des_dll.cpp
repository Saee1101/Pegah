#include "preform_des_dll.h"

#include <cmath>

#include "pre_process.h"
#include "head_defect.h"
#include "oval_measurement.h"
#include "ring_defect.h"
#include "post_pro.h"



using namespace HalconCpp;

Preform_des_dll::Preform_des_dll(HalconCpp::HImage Image, double max_oval, double min_oval  , double limit_ring, double limit_head, double pixel_way1, double pixel_way2, int threshold)
    : flag_ring(false), flag_head(false), flag_oval(false), score_ring(0.0), score_head(0.0) ,max_ov(0.0), min_ov(0.0)

{

   // Pre-process the image
   pre_process preProcessor(Image, threshold, 3.5);

   // Perform defect analysis
   head_defect headAnalyzer(preProcessor.head, 10.5);
   oval_measurement ovalAnalyzer(preProcessor.oval, 10, pixel_way1, pixel_way2);
   ring_defect ringAnalyzer(preProcessor.ring, preProcessor.Row, preProcessor.Column, preProcessor.Radius, 10.5);


   // Post-process results
   post_pro postProcessor(Image, preProcessor.oval, ringAnalyzer.ring_defects, headAnalyzer.head_defects);

   // Calculate region features
   RegionFeatures(ringAnalyzer.ring_defects, "area", &score_ring);
   RegionFeatures(headAnalyzer.head_defects, "area", &score_head);

   // Determine flags based on thresholds
   try {
       flag_oval = (ovalAnalyzer.outmax1 < max_oval) && (ovalAnalyzer.outmin1 > min_oval);
       flag_ring = (score_ring.D() < limit_ring);
       flag_head = (score_head.D() < limit_head);
   } catch (...) {
       flag_oval = 0;
       flag_ring = 0;
       flag_head = 0;
   }

   // Normalize scores
   try {
       score_ring = 1.0 / (score_ring.D() / 250.0 + 1.0) * 100.0;
       score_head = 1.0 / (score_head.D() / 250.0 + 1.0) * 100.0;
   } catch (...) {
       score_ring = 0;
       score_head = 0;
   }

   // Update results
   try {
       max_ov = std::isnan(ovalAnalyzer.outmax1) ? 0 : ovalAnalyzer.outmax1;
       min_ov = std::isnan(ovalAnalyzer.outmin1) ? 0 : ovalAnalyzer.outmin1;
       image = postProcessor.output_image;
   } catch (...) {
       max_ov = 0;
       min_ov = 0;
       image = Image;
   }

}

// Getter methods for flags
bool Preform_des_dll::get_flag_ring()  { return flag_ring;}
bool Preform_des_dll::get_flag_head()  { return flag_head; }
bool Preform_des_dll::get_flag_oval()  { return flag_oval; }

// Getter methods for oval measurements
double Preform_des_dll::get_max_oval()  {return max_ov;}
double Preform_des_dll::get_min_oval()  {return min_ov;}

// Getter methods for scores
double Preform_des_dll::get_score_ring()  { return score_ring; }
double Preform_des_dll::get_score_head()  { return score_head; }

// Getter method for the processed image
HImage Preform_des_dll::get_image()  { return image; }
