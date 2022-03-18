#include "UserWindow.h"
#include <QFile>
#include <QUrl>
#include <QDesktopServices>
#include <QMessageBox>

UserWindow::UserWindow(UserServices &services, QWidget *parent) :
    QMainWindow(parent),
    services {services},
    mainWidget {new QWidget(this)},
    mainLayout {new QVBoxLayout(mainWidget)}
{
    setCentralWidget(mainWidget);

    InitializeBottomButtonLayout();

    InitializeAttributesBox();

    mainLayout->addWidget(attributesBox);
    mainLayout->addLayout(buttonsLayout);

    ConnectSignalsAndSlots(parent);
}

void UserWindow::closeEvent(QCloseEvent *e)
{
    QMainWindow::closeEvent(e);
    emit windowClosed();
}

void UserWindow::ConnectSignalsAndSlots(QWidget *parent)
{
    connect(startButton, SIGNAL(clicked()), this, SLOT(StartIterating()));
    connect(viewPhotoButton, SIGNAL(clicked()), this, SLOT(ViewPhoto()));
    connect(adoptButton, SIGNAL(clicked()), this, SLOT(AdoptDog()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(SkipDog()));
    connect(filterButton, SIGNAL(clicked()), this, SLOT(OpenFilterWindow()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(StopViewing()));
    connect(viewAdoptionListButton, SIGNAL(clicked()), this, SLOT(OpenTypeWindow()));
    connect(this, SIGNAL(windowClosed()), parent, SLOT(DeleteUserWindow()));
}

void UserWindow::InitializeButton(QPushButton *button)
{
    QFile file("../KeepCalmAndAdoptAPet_V4/Stylesheets/AdminButton.qss");
    file.open(QFile::ReadOnly);
    QString str = file.readAll();
    button->setStyleSheet(str);
    file.close();
}

void UserWindow::InitializeLineEdit(QLineEdit *lineEdit)
{
    lineEdit->setReadOnly(true);
}

void UserWindow::InitializeBottomButtonLayout()
{
    buttonsLayout = new QHBoxLayout();

    startButton = new QPushButton(mainWidget);
    startButton->setText("Start viewing dogs");
    filterButton = new QPushButton(mainWidget);
    filterButton->setText("Filter dogs");
    stopButton = new QPushButton(mainWidget);
    stopButton->setText("Stop viewing dogs");
    stopButton->setDisabled(true);
    viewAdoptionListButton = new QPushButton(mainWidget);
    viewAdoptionListButton->setText("View adoption list");
    InitializeButton(startButton);
    InitializeButton(filterButton);
    InitializeButton(stopButton);
    InitializeButton(viewAdoptionListButton);
    buttonsLayout->addWidget(startButton);
    buttonsLayout->addWidget(filterButton);
    buttonsLayout->addWidget(stopButton);
    buttonsLayout->addWidget(viewAdoptionListButton);
}

void UserWindow::InitializeAttributesBox()
{
    attributesBox = new QGroupBox("Dog Attributes", mainWidget);

    nameLE = new QLineEdit(attributesBox);
    ageLE = new QLineEdit(attributesBox);
    breedLE = new QLineEdit(attributesBox);
    viewPhotoButton = new QPushButton(attributesBox);
    viewPhotoButton->setDisabled(true);
    viewPhotoButton->setText("View a photo of the dog");

    InitializeLineEdit(nameLE);
    InitializeLineEdit(ageLE);
    InitializeLineEdit(breedLE);
    InitializeButton(viewPhotoButton);

    InitializeAdoptionButtonsLayout();
    InitializeAttributesLayout();

    attributesBox->setLayout(attributesLayout);
}

void UserWindow::InitializeAttributesLayout()
{
    attributesLayout = new QFormLayout();

    attributesLayout->addRow("&Name:", nameLE);
    attributesLayout->addRow("&Age:", ageLE);
    attributesLayout->addRow("&Breed:", breedLE);
    attributesLayout->addRow("&Photograph:", viewPhotoButton);
    attributesLayout->addRow(adoptionButtonsLayout);
}

void UserWindow::InitializeAdoptionButtonsLayout()
{
    adoptionButtonsLayout = new QHBoxLayout();

    adoptButton = new QPushButton(attributesBox);
    adoptButton->setText("Adopt this dog");
    adoptButton->setDisabled(true);
    nextButton = new QPushButton(attributesBox);
    nextButton->setText("Skip to the next dog");
    nextButton->setDisabled(true);
    InitializeButton(adoptButton);
    InitializeButton(nextButton);
    adoptionButtonsLayout->addWidget(adoptButton);
    adoptionButtonsLayout->addWidget(nextButton);
}

void UserWindow::StartIterating()
{
    services.ReinitializeDogList();

    adoptButton->setDisabled(false);
    nextButton->setDisabled(false);
    auto currentDog = services.GetCurrentDog();
    nameLE->setText(QString::fromStdString(currentDog.GetName()));
    breedLE->setText(QString::fromStdString(currentDog.GetBreed()));
    ageLE->setText(QString::number(currentDog.GetAge()));
    viewPhotoButton->setEnabled(true);

    startButton->setDisabled(true);
    filterButton->setDisabled(true);
    stopButton->setEnabled(true);
}

void UserWindow::ViewPhoto()
{
    QDesktopServices::openUrl(QUrl(QString::fromStdString(services.GetCurrentDog().GetPhotograph())));
}

void UserWindow::AdoptDog()
{
    try
    {
        services.AddToAdoptionList(services.GetCurrentDog());
        auto currentDog = services.GetCurrentDog();
        nameLE->setText(QString::fromStdString(currentDog.GetName()));
        breedLE->setText(QString::fromStdString(currentDog.GetBreed()));
        ageLE->setText(QString::number(currentDog.GetAge()));
    }
    catch (AdoptionListException& ex)
    {
        QMessageBox::warning(this, "Error!", ex.what());
        SkipDog();
    }
}

void UserWindow::SkipDog()
{
    services.GoToNextDog();
    auto currentDog = services.GetCurrentDog();
    nameLE->setText(QString::fromStdString(currentDog.GetName()));
    breedLE->setText(QString::fromStdString(currentDog.GetBreed()));
    ageLE->setText(QString::number(currentDog.GetAge()));
}

void UserWindow::StopViewing()
{
    nameLE->setText("");
    breedLE->setText("");
    ageLE->setText("");
    adoptButton->setDisabled(true);
    nextButton->setDisabled(true);
    viewPhotoButton->setDisabled(true);

    stopButton->setDisabled(true);
    startButton->setEnabled(true);
    filterButton->setEnabled(true);
}

void UserWindow::OpenFilterWindow()
{
    filterWindow = new FilterWindow(services, this);

    filterWindow->show();
}

void UserWindow::DeleteFilterWindow(QString breed, int age)
{
    delete filterWindow;
    filterWindow = nullptr;

    if (breed == "" && age == -1)
    {
        QMessageBox::warning(this, "Error!", "Window closed with no parameters given!");
    }
    else
    {
        services.FilterByBreedAndAge(breed.toStdString(), age);
        adoptButton->setDisabled(false);
        nextButton->setDisabled(false);
        auto currentDog = services.GetCurrentDog();
        nameLE->setText(QString::fromStdString(currentDog.GetName()));
        breedLE->setText(QString::fromStdString(currentDog.GetBreed()));
        ageLE->setText(QString::number(currentDog.GetAge()));
        viewPhotoButton->setEnabled(true);

        startButton->setDisabled(true);
        filterButton->setDisabled(true);
        stopButton->setEnabled(true);
    }
}

void UserWindow::OpenTypeWindow()
{
    typeWindow = new AdoptionListTypeWindow(services, this);

    typeWindow->show();
}

void UserWindow::DeleteTypeWindow(QString mode)
{
    delete typeWindow;
    typeWindow = nullptr;

    try
    {
        services.SetWriteMode(mode.toStdString());

        if (services.GetWriteMode() == "HTML")
        {
            services.WriteData();
            QDesktopServices::openUrl(QUrl::fromLocalFile("adoption_list.html"));
        }
        else if (services.GetWriteMode() == "CSV")
        {
            services.WriteData();
            QDesktopServices::openUrl(QUrl::fromLocalFile("adoption_list.csv"));
        }
        else if (services.GetWriteMode() == "InApp")
        {
            openViewWindow();
        }
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error!", "No mode was selected!");
    }

}

void UserWindow::openViewWindow()
{
    listViewer = new AdoptionListViewer(services.GetAdoptionList(), this);

    listViewer->show();
}

void UserWindow::deleteViewWindow()
{
    delete listViewer;

    listViewer = nullptr;
}
