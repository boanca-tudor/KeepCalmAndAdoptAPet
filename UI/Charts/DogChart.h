#ifndef DOGCHART_H
#define DOGCHART_H

#include <QMainWindow>
#include <QChart>
#include <QBarSeries>
#include <QChart>
#include <QVBoxLayout>
#include "Business/AdminServices.h"

class DogChart : public QMainWindow
{
    Q_OBJECT
public:
    explicit DogChart(AdminServices& services, QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent* e) override;
private:
    void ConnectSignalsAndSlots(QWidget* parent);
    void SetupChart();

    AdminServices& services;
    QtCharts::QBarSeries* series;
    QWidget* mainWidget;
    QVBoxLayout* mainLayout;
    QtCharts::QChart* chart;
signals:
    void windowClosed();
};

#endif // DOGCHART_H
