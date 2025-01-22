#ifndef GALLERY_H
#define GALLERY_H

#include <QObject>
#include <QListWidget>
#include <QListWidgetItem>
#include "halconqtwindow.h"
using namespace HalconCpp;
class gallery : public QObject
{
    Q_OBJECT
public:
    explicit gallery(QObject *parent,QListWidget*WL);
    void Set_Gallery(QListWidget*WL);
    QListWidget* QListWidget_;
     QVector<halconqtwindow*> HWindowList;
    QVector<HalconCpp::HImage*> imageList;
     halconqtwindow *windowforbigimage;
     int ItemCount;
    void Set_ItemGallery(int number,int width,int height,int space);
    void Add_Image(HImage* im);
    void set_window(halconqtwindow*);
    int selsectedItem;
signals:
};

#endif // GALLERY_H
