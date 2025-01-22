#ifndef SETTING_CAMERA_DB_H
#define SETTING_CAMERA_DB_H
#include <QString>
#include "Entities.h"
class setting_camera_db : public Entities
{
public:
    setting_camera_db ()= default;
    ~setting_camera_db ()= default;
    QString tableName() const override   {return "Setting_camera";}

};
#endif // SETTING_CAMERA_DB_H
