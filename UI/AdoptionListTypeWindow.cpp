#include "AdoptionListTypeWindow.h"

AdoptionListTypeWindow::AdoptionListTypeWindow(UserServices &services, QWidget *parent) :
    QMainWindow(parent),
    services {services},
    mainWidget {new QWidget(this)}
{
    InitializeLayout();

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    ConnectSignalsAndSlots(parent);
}

void AdoptionListTypeWindow::closeEvent(QCloseEvent *e)
{
    QMainWindow::closeEvent(e);
    if (htmlRB->isChecked())
        emit closeWindow("HTML");
    else if (csvRB->isChecked())
        emit closeWindow("CSV");
    else if (inAppRB->isChecked())
        emit closeWindow("InApp");
    else
        emit closeWindow("");
}

void AdoptionListTypeWindow::ConnectSignalsAndSlots(QObject *parent)
{
    connect(this, SIGNAL(closeWindow(QString)), parent, SLOT(DeleteTypeWindow(QString)));
    connect(selectButton, SIGNAL(clicked()), this, SLOT(selectType()));
}

void AdoptionListTypeWindow::InitializeLayout()
{
    mainLayout = new QFormLayout(this->centralWidget());
    htmlRB = new QRadioButton(tr("&HTML"), this->centralWidget());
    csvRB = new QRadioButton(tr("&CSV"), this->centralWidget());
    inAppRB = new QRadioButton(tr("&In App"), this->centralWidget());
    selectButton = new QPushButton(tr("&Done"), this->centralWidget());
    mainLayout->addRow(htmlRB);
    mainLayout->addRow(csvRB);
    mainLayout->addRow(inAppRB);
    mainLayout->addRow(selectButton);
}

void AdoptionListTypeWindow::selectType()
{
    close();
}
