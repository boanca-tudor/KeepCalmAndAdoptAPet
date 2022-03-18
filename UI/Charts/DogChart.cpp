#include "DogChart.h"
#include <QBarSet>
#include <QValueAxis>
#include <QChartView>

DogChart::DogChart(AdminServices& services, QWidget *parent) :
    QMainWindow(parent),
    services {services},
    mainWidget {new QWidget(this)}
{
    mainLayout = new QVBoxLayout(mainWidget);
    mainWidget->setLayout(mainLayout);

    resize(800, 600);

    SetupChart();

    setCentralWidget(mainWidget);

    ConnectSignalsAndSlots(parent);
}

void DogChart::closeEvent(QCloseEvent *e)
{
    QMainWindow::closeEvent(e);
    emit windowClosed();
}

void DogChart::ConnectSignalsAndSlots(QWidget *parent)
{
    connect(this, SIGNAL(windowClosed()), parent, SLOT(DeleteChartWindow()));
}

void DogChart::SetupChart()
{
    auto dogs = services.GetRepo().GetArray();
    std::vector<std::pair<std::string, int>> pairs;
    bool found;
    for (auto& dog : dogs)
    {
        found = false;
        for (auto& pair : pairs)
            if (dog.GetBreed() == pair.first)
            {
                pair.second++;
                found = true;
                break;
            }

        if (!found)
            pairs.push_back({dog.GetBreed(), 1});
    }

    series = new QtCharts::QBarSeries(this);
    for (auto& pair : pairs)
    {
        QtCharts::QBarSet* newSet = new QtCharts::QBarSet(QString::fromStdString(pair.first));
        *newSet << pair.second;
        series->append(newSet);
    }

    QtCharts::QChart* chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Dog data");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QValueAxis* axisY = new QtCharts::QValueAxis();
    int max = -1;
    for (auto& pair : pairs)
        max = std::max(max, pair.second);
    axisY->setRange(0, max);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);


    QtCharts::QChartView* view = new QtCharts::QChartView(chart, this);
    view->setRenderHint(QPainter::Antialiasing);

    mainLayout->addWidget(view);
}
