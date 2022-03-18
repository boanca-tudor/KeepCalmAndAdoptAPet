#include "UI/ModeWindow.h"
#include <memory>
#include <QDebug>
#include <QFile>
#include <QPixmap>
#include <QBitmap>
#include <QDesktopWidget>
#include <QApplication>

ModeWindow::ModeWindow(AdminServices &adminServices, UserServices &userServices, UndoServices &undoServices, QWidget *parent) :
    QMainWindow(parent),
    adminServices {adminServices},
    userServices {userServices},
    undoServices {undoServices},
    mainWidget {new QWidget(this)},
    adminWindow {nullptr},
    layout {new QVBoxLayout(mainWidget)},
    userButton {new QPushButton(tr("User Mode"), mainWidget)},
    adminButton {new QPushButton(tr("Administrator Mode"), mainWidget)},
    chartButton {new QPushButton(tr("Chart Mode"), mainWidget)},
    imageLabel {new QLabel(mainWidget)}
{
    InitializeImageLabel(imageLabel, "../KeepCalmAndAdoptAPet_V4/Images/KeepCalm.png");

    InitializeButton(userButton);
    InitializeButton(adminButton);
    InitializeButton(chartButton);

    layout->addWidget(imageLabel);
    layout->addWidget(adminButton);
    layout->addWidget(userButton);
    layout->addWidget(chartButton);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);
    QCoreApplication::setApplicationName("Keep Calm and Adopt a Pet");
    ConnectSignalsAndSlots();
}

ModeWindow::~ModeWindow()
{
    delete imageLabel;
    delete userButton;
    delete adminButton;
    delete layout;
}

void ModeWindow::ConnectSignalsAndSlots()
{
    connect(adminButton, SIGNAL(clicked()), this, SLOT(OpenAdminWindow()));
    connect(userButton, SIGNAL(clicked()), this, SLOT(OpenUserWindow()));
    connect(chartButton, SIGNAL(clicked()), this, SLOT(OpenChartWindow()));
}

void ModeWindow::InitializeButton(QPushButton *button)
{
    QFile file("../KeepCalmAndAdoptAPet_V4/Stylesheets/ModeButton.qss");
    file.open(QFile::ReadOnly);
    QString str = file.readAll();
    button->setStyleSheet(str);
    file.close();
}

void ModeWindow::InitializeImageLabel(QLabel *label, QString path)
{
    QPixmap pixmap(path);
    pixmap = pixmap.scaled(800, 600, Qt::KeepAspectRatio);
    label->setPixmap(pixmap);
    label->setMask(pixmap.mask());

    label->setScaledContents(true);
}

void ModeWindow::OpenAdminWindow()
{
    adminWindow = new AdministratorWindow(adminServices, undoServices, this);

    adminWindow->show();
}

void ModeWindow::OpenUserWindow()
{
    userWindow = new UserWindow(userServices, this);

    userWindow->show();
}

void ModeWindow::OpenChartWindow()
{
    chartWindow = new DogChart(adminServices, this);

    chartWindow->show();
}

void ModeWindow::DeleteAdminWindow()
{
    qDebug() << "Destroyed admin window";
    delete adminWindow;
    adminWindow = nullptr;
}

void ModeWindow::DeleteUserWindow()
{
    qDebug() << "Destroyed user window";
    delete userWindow;
    userWindow = nullptr;
}

void ModeWindow::DeleteChartWindow()
{
    qDebug() << "Destroyed chart window";
    delete chartWindow;
    chartWindow = nullptr;
}

