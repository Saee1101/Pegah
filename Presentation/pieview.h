#ifndef PIEVIEW_H
#define PIEVIEW_H

#include <QObject>
#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCore/QTimer>
#include<QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QFormLayout>
#include <QGraphicsItem>
// QT_CHARTS_USE_NAMESPACE
class pieview : public QChart
{
    Q_OBJECT
public:
    explicit pieview(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());

    // explicit pieview(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
QPieSeries *series;
signals:

};

#endif // PIEVIEW_H
