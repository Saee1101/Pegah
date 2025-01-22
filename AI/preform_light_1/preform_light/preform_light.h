#ifndef PREFORM_LIGHT_H
#define PREFORM_LIGHT_H
#include "HalconCpp.h"
#include "HDevThread.h"
#include "preform_light_global.h"
using namespace HalconCpp;
class PREFORM_LIGHT_EXPORT Preform_light
{
public:
    Preform_light(const char *path);
    void get_json_path(const char* path);
    void process(HalconCpp::HImage input_image, double sigma = .3, int threshold = 60);

    double score;

private:
    const char* json_path;
};

#endif // PREFORM_LIGHT_H
