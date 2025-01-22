#ifndef SETTING_PRODUCT_DB_H
#define SETTING_PRODUCT_DB_H
#include <QString>
#include "Entities.h"
class setting_product_db : public Entities
{
public:
    setting_product_db ()= default;
    ~setting_product_db ()= default;
     QString tableName() const override   {return "Setting_product";}
};
#endif // SETTING_PRODUCT_DB_H
