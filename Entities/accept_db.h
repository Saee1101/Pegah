#ifndef ACCEPT_DB_H
#define ACCEPT_DB_H
#include <QString>
#include "Entities.h"
class accept_db: public Entities
{
public:
    accept_db ()= default;
    ~accept_db ()= default;
    QString tableName() const override   {return "accept";}

};
#endif // ACCEPT_DB_H
