#include "ShamsiDateEdit.h"
#include <QHBoxLayout>

ShamsiDateEdit::ShamsiDateEdit(QWidget *parent)
    : QWidget{parent}
{
    increase_pushbutton=new QPushButton(this);
    increase_pushbutton->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Up.svg);");
    increase_pushbutton->setFixedSize(43,44);
    increase_pushbutton->setFocusPolicy(Qt::NoFocus);
    decrease_pushbutton=new QPushButton(this);
    decrease_pushbutton->setStyleSheet("image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Up-1.svg);");
    decrease_pushbutton->setFixedSize(43,44);
    decrease_pushbutton->setFocusPolicy(Qt::NoFocus);



    lineEdit = new QLineEdit(this);
    lineEdit->setStyleSheet("border-image: url(:/Tivanex - App Ui - Preform/Tivanex - App Ui 04 - Page 3/Group 269.svg);"
                            "	color: rgb(255, 255, 255);"
                            "font-family: 'SegoeUI'; font-size: 20px;");
    lineEdit->setFixedSize(208,44);
    lineEdit->setAlignment(Qt::AlignCenter);


    QHBoxLayout *layout = new QHBoxLayout(this);
    // layout->setSpacing(5);
    // layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(lineEdit);
    layout->addWidget(increase_pushbutton);
    layout->addWidget(decrease_pushbutton);
    setLayout(layout);

    lineEdit->setPlaceholderText("1403/10/10");


    connect(increase_pushbutton,&QPushButton::clicked,this,&ShamsiDateEdit::onDateChanged_increase);
    connect(decrease_pushbutton,&QPushButton::clicked,this,&ShamsiDateEdit::onDateChanged_decrease);
     connect(lineEdit, &QLineEdit::textChanged, this, &ShamsiDateEdit::onDateChanged);

}

void ShamsiDateEdit::onDateChanged_increase()
{
 selectionStart = lineEdit->selectionStart();
    switch (lineEdit->selectionStart()) {
    case 0:
        emit increase(0);
        break;
    case 5:
        emit increase(5);
        break;
    case 8:
        emit increase(8);
    }


}

void ShamsiDateEdit::onDateChanged_decrease()
{
    selectionStart = lineEdit->selectionStart();
    switch (lineEdit->selectionStart()) {
    case 0:
        emit decrease(0);
        break;
    case 5:
        emit decrease(5);
        break;
    case 8:
        emit decrease(8);
    }
}

void ShamsiDateEdit::updateLineEdit() {
    // QString formattedDate = QString("%1/%2/%3")
    // .arg(currentYear)
    //     .arg(currentMonth, 2, 10, QChar('0'))
    //     .arg(currentDay, 2, 10, QChar('0'));

    // lineEdit->setText(formattedDate);
    // qDebug()<<"selectionStart :"<<selectionStart;
    // lineEdit->setSelection(selectionStart, formattedDate.length());
    QString formattedDate = QString("%1/%2/%3")
                                .arg(currentYear)
                                .arg(currentMonth, 2, 10, QChar('0'))
                                .arg(currentDay, 2, 10, QChar('0'));

    lineEdit->setText(formattedDate);

    if (selectionStart >= 0 && selectionStart < 5) {
        lineEdit->setSelection(selectionStart, 4);

    } else if (selectionStart >= 5 && selectionStart < formattedDate.length())
    {
        lineEdit->setSelection(selectionStart, 2);

}
}

void ShamsiDateEdit::onDateChanged()
{
    QString input = lineEdit->text();
    emit dateChanged(input);

}
