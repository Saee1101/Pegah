#ifndef ENTITIES_H
#define ENTITIES_H

#include "Entities_global.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

#include "Repository.h"


class Entities
{

public:
    Entities()= default;
    virtual ~ Entities()= default ;
    virtual QString tableName() const = 0;
    int get_id() const { return id_; }
    void set_id(int id) { id_ = id; }

    QString get_key() const { return key_; }
    void set_key(const QString& key) { key_ = key; }

    QString get_value() const { return value_; }
    void set_value(QString value) { value_ = value; }
protected:
    int id_;
    QString key_;
    QString value_;
};

#endif // ENTITIES_H
