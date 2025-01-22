#ifndef REJECT_DB_H
#define REJECT_DB_H
#include <QString>
#include "Entities.h"
class reject_db: public Entities
{
public:
    reject_db ()= default;
    ~reject_db ()= default;
    QString tableName() const override   {return "Reject";}

};
#endif // REJECT_DB_H
