#ifndef SETTING_USER_DB_H
#define SETTING_USER_DB_H

#include <QString>
#include "Entities.h"
class  setting_user_db : public Entities
{
public:
   setting_user_db ()= default;
    ~setting_user_db ()= default;
      QString tableName() const override {return "Setting_user";}
};

#endif // SETTING_USER_DB_H
