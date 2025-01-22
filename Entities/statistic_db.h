#ifndef STATISTIC_DB_H
#define STATISTIC_DB_H
#include <QString>
#include "Entities.h"
class statistic_db : public Entities
{

public:
    statistic_db ()= default;
    ~statistic_db ()= default;
   QString tableName() const override   {return "Statistic";}



};

#endif // STATISTIC_DB_H
