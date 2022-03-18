#include "UI/FilterWindow.h"

FilterWindow::FilterWindow(UserServices &services, QWidget *parent) :
    QMainWindow(parent),
    services {services},
    mainWidget {new QWidget(this)},
    mainLayout {new QFormLayout(mainWidget)}
{
    setCentralWidget(mainWidget);

    InitializeLayout();

    ConnectSignalsAndSlots(parent);
}

void FilterWindow::closeEvent(QCloseEvent *e)
{
    QMainWindow::closeEvent(e);
    if (breedLE->text() == "" && ageSB->value() == 0)
    {
        emit closeWindow("", -1);
    }
    else
    {
        emit closeWindow(breedLE->text(), ageSB->value());
    }

}

void FilterWindow::ConnectSignalsAndSlots(QWidget* parent)
{
    connect(this, SIGNAL(closeWindow(QString, int)), parent, SLOT(DeleteFilterWindow(QString, int)));
    connect(filterButton, SIGNAL(clicked()), this, SLOT(Filter()));
}

void FilterWindow::InitializeLayout()
{
    breedLE = new QLineEdit(mainWidget);
    ageSB = new QSpinBox(mainWidget);
    mainLayout->addRow(tr("&Breed:"), breedLE);
    mainLayout->addRow(tr("&Maximum age:"), ageSB);

    filterButton = new QPushButton(tr("Filter"), mainWidget);
    mainLayout->addRow(filterButton);
}

void FilterWindow::Filter()
{
    services.FilterByBreedAndAge(breedLE->text().toStdString(), ageSB->value());

    close();
}

