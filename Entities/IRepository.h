#ifndef IREPOSITORY_H
#define IREPOSITORY_H
#include <QObject>
#include <QSqlTableModel>
class IREPOSITORY {

    void Add();
    void Delete();
    QSqlTableModel* GetAll();
    void Update();
        // virtual void Add(const QString& key, double value = 0.0) = 0;
        // virtual void Delete(int id) = 0;
        // virtual QSqlTableModel* GetAll() = 0;
        // virtual void Update(int id, const QString& key, double value = 0.0) = 0;
};
Q_DECLARE_INTERFACE(IREPOSITORY,"IREPOSITORY")
#endif // IREPOSITORY_H
