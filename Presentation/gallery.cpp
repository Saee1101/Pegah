#include "gallery.h"

gallery::gallery(QObject *parent,QListWidget*WL)
    : QObject{parent}
{
    Set_Gallery(WL);
    connect(QListWidget_,&QListWidget::itemClicked,[this](QListWidgetItem* item){
        if(item &&QListWidget_->row(item)<imageList.length()){
           selsectedItem= QListWidget_->row(item);
            HImage imageforwindow=*imageList.at(selsectedItem);
            Hlong Width,Height;
            imageforwindow.GetImageSize(&Width,&Height);
            // AI_image_CL->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
            windowforbigimage->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
            imageforwindow.DispImage(windowforbigimage->WinfoeID());

        }
    });
}

void gallery::Set_Gallery(QListWidget *WL)
{
    QListWidget_=WL;
}

void gallery::Set_ItemGallery(int number,int width,int height,int space)
{
    ItemCount=number;
    QListWidget_->setViewMode(QListView::ListMode);
    // ui->Gallery->setIconSize(QSize(10, 10));
    QListWidget_->setResizeMode(QListView::Adjust);
   QListWidget_->setSpacing(space);
    QListWidget_->setFlow(QListView::LeftToRight);
    Hlong Width,Height;
    Width=width;
    Height=height;
    // qDebug()<<"HERE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
    for (int i = 0 ; i < number ; i++){
        halconqtwindow *newwindow=new halconqtwindow();
        newwindow->openwindow(width,height);
        newwindow->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(Height-1),HalconCpp::HTuple(Width-1));
        HWindowList.append(newwindow);
        // qDebug() << "hal " << i << " is :::" <<HWindowList.at(i);

        // QWidget* widget = new QWidget(ui->Gallery);
        //        QHBoxLayout* layout = new QHBoxLayout(widget);
        //        layout->setContentsMargins(0, 0, 0, 0);
        //        layout->setSpacing(0);
        //        layout->addWidget(newwindow);

        QListWidgetItem* item = new QListWidgetItem(QListWidget_);
        item->setSizeHint(QSize(width, height));
        QListWidget_->addItem(item);
        QListWidget_->setItemWidget(item, newwindow);
    }
}

void gallery::Add_Image(HImage *image)
{

    HImage newimage = image->CopyImage();
    if (imageList.size() < ItemCount) {
        imageList.append(new HImage(newimage));
    } else {
        imageList.pop_front();
        imageList.push_back(new HImage(newimage));
    }

    for (int i = 0; i < imageList.size(); i++) {
        Hlong width, height;
        imageList.at(i)->GetImageSize(&width, &height);
        HWindowList.at(i)->WinfoeID().SetPart(HalconCpp::HTuple(0),HalconCpp::HTuple(0),HalconCpp::HTuple(height-1),HalconCpp::HTuple(width-1));
        imageList.at(i)->DispImage(HWindowList.at(i)->WinfoeID());
    }
}

void gallery::set_window(halconqtwindow *w)
{
    windowforbigimage = w;
}
