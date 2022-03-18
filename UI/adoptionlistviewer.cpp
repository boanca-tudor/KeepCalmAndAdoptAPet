#include "adoptionlistviewer.h"

AdoptionListViewer::AdoptionListViewer(const AdoptionList &list, QWidget *parent) :
    QMainWindow(parent),
    adoptionList {list},
    mainWidget {new QWidget(this)}
{
    InitializeLayout();

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    ConnectSignalsAndSlots(parent);
}

void AdoptionListViewer::closeEvent(QCloseEvent *e)
{
    QMainWindow::closeEvent(e);
    emit windowClosed();
}

void AdoptionListViewer::ConnectSignalsAndSlots(QWidget *parent)
{
    connect(this, SIGNAL(windowClosed()), parent, SLOT(deleteViewWindow()));
}

void AdoptionListViewer::InitializeView()
{
    adoptionListView = new QTableView(mainWidget);

    AdoptionListModel* listModel = new AdoptionListModel(adoptionList);

    adoptionListView->setModel(listModel);
}

void AdoptionListViewer::InitializeLayout()
{
    mainLayout = new QVBoxLayout();

    InitializeView();

    mainLayout->addWidget(adoptionListView);
}
