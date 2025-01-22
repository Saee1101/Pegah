#ifndef SHAMSIDATEEDIT_H
#define SHAMSIDATEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class ShamsiDateEdit : public QWidget
{
    Q_OBJECT
public:
    explicit ShamsiDateEdit(QWidget *parent = nullptr);
    int currentYear;
    int currentMonth;
    int currentDay;
    void updateLineEdit();
signals:
private:

    int selectionStart;
    QLineEdit *lineEdit;
    QPushButton *increase_pushbutton;
    QPushButton *decrease_pushbutton;
private slots:
     void onDateChanged();
    void onDateChanged_increase();
     void onDateChanged_decrease();
signals:
    void dateChanged(const QString &newDate);
    void increase(int);
    void decrease(int);
    void text_current(QString);
};

#endif // SHAMSIDATEEDIT_H
