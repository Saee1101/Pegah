#ifndef SETTING_USER_ROLE_DB_H
#define SETTING_USER_ROLE_DB_H
#include <QString>
#include "Entities.h"
class  setting_user_role_db : public Entities
{
public:
    setting_user_role_db()= default;
    ~setting_user_role_db ()= default;
    QString tableName() const override {return "Setting_user_role";}
};

#endif // SETTING_USER_ROLE_DB_H
