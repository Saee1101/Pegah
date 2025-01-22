#ifndef REPOSITORY_H
#define REPOSITORY_H


#include "IRepository.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QtCore>

template <typename T>
class Repository
{
     // Q_INTERFACES(IREPOSITORY);

public:

    explicit Repository();
     ~ Repository()=default;
    void Add(const QString& key,QString value) ;
    void Delete(const QString& key) ;
    QSqlTableModel* GetAll() ;
    void Update(const QString& key,QString value) ;

private :
    QSqlDatabase db ;
    // QSqlTableModel* model;
    QString tablename ,databaseType ,databaseName;
    void ConnectionDB ();
    T obj;



};

template <typename T>
Repository<T>::Repository()
{
    tablename=obj.tableName();
    QString JsonFilePath="DBconnectionconfig.json";
    QFile file(JsonFilePath);
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray Bytes=file.readAll();
        file.close();

        QJsonParseError JsonError;
        QJsonDocument Document=QJsonDocument::fromJson(Bytes,&JsonError);
        if(JsonError.error != QJsonParseError::NoError)
        {
            qDebug()<<"Error In Json DB";
        }
        if(Document.isObject())
        {
            QJsonObject obj=Document.object();
            databaseType =obj.value("databaseType").toString();
            databaseName =obj.value("databaseName").toString();
        }

    }
    ConnectionDB ();

}

template <typename T>
void Repository<T>::Add(const QString& key,QString value)
{

    T item;
    item.set_key(key);
    item.set_value(value);

    QSqlQuery q;
    q.prepare(QString("INSERT INTO %1 (key_, value_) VALUES (:key, :value)").arg(tablename));
    q.bindValue(":key", item.get_key());
    q.bindValue(":value", item.get_value());
    if (!q.exec()) {
        qDebug() << "Error executing Add query:" ;
    }
}
template <typename T>
void Repository<T>::Delete(const QString& key)
{
    T item;
    item.set_key(key);

    QSqlQuery q;
    q.prepare(QString("DELETE FROM %1 WHERE key_=:key").arg(tablename));
    q.bindValue(":key",item.get_key());
    if (!q.exec()) {
        qDebug() << "Error executing Delete query:" ;
    }
}
template <typename T>
QSqlTableModel* Repository<T>::GetAll( )
{

       QSqlTableModel* model=new QSqlTableModel();
       model->setTable(tablename);
       model->select();
       return model;

}
template <typename T>
void Repository<T>::Update(const QString& key,QString value)
{

    T item;
    item.set_key(key);
    item.set_value(value);

    QSqlQuery q;
    q.prepare(QString("UPDATE %1 SET key_=:key, value_=:value WHERE key_=:key ").arg(tablename));
    q.bindValue(":key",item.get_key());
    q.bindValue(":value",item.get_value());
    if (!q.exec()) {
        // qDebug() << "Error executing Update query:" << q.lastError().text();
    }
}
template <typename T>
void Repository<T>::ConnectionDB ()
{

    db=QSqlDatabase :: addDatabase(databaseType);
    db.setDatabaseName(databaseName);
    if(!db.open())
    {
        qDebug() << "Entities::Repository.h::'Failed to open the database!'";
    }
}
#endif // REPOSITORY_H
