#include "UI/AdministratorWindow.h"
#include <QMessageBox>
#include <QFile>

AdministratorWindow::AdministratorWindow(AdminServices &services, UndoServices &undoServices, QWidget *parent) :
    QMainWindow(parent),
    services {services},
    undoServices {undoServices},
    mainWidget {new QWidget(this)},
    layout {new QVBoxLayout(mainWidget)},
    addWindow {nullptr}
{
    resize(850, 650);
    mainWidget->resize(800, 600);
    InitializeTable();
    InitializeEditBox();
    InitializeUndoRedoLayout();
    InitializeButton();
    InitializeShortcuts();

    layout->addWidget(dogTable);
    layout->addWidget(editGroupBox);
    layout->addLayout(undoRedoLayout);
    layout->addWidget(exitButton);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    ConnectSignalsAndSlots(parent);
}

AdministratorWindow::~AdministratorWindow()
{
    delete mainWidget;
}

void AdministratorWindow::closeEvent(QCloseEvent *e)
{
    QMainWindow::closeEvent(e);
    emit windowClosed();
}

void AdministratorWindow::ConnectSignalsAndSlots(QWidget* parent)
{
    connect(exitButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
    connect(dogTable, SIGNAL(cellClicked(int, int)), this, SLOT(loadDogAttributes(int)));
    connect(addButton, SIGNAL(clicked()), this, SLOT(openNewAddWindow()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeDog()));
    connect(updateButton, SIGNAL(clicked()), this, SLOT(updateDog()));
    connect(this, SIGNAL(windowClosed()), parent, SLOT(DeleteAdminWindow()));
    connect(shortcuts[0], SIGNAL(activated()), this, SLOT(undo()));
    connect(shortcuts[1], SIGNAL(activated()), this, SLOT(redo()));
    connect(undoButton, SIGNAL(clicked()), this, SLOT(undo()));
    connect(redoButton, SIGNAL(clicked()), this, SLOT(redo()));
}

void AdministratorWindow::closeWindow()
{
    close();
}

void AdministratorWindow::loadDogAttributes(int row)
{
    if (!nameLineEdit->isEnabled()) nameLineEdit->setEnabled(true);
    if (!ageSpinBox->isEnabled()) ageSpinBox->setEnabled(true);
    if (!breedLineEdit->isEnabled()) breedLineEdit->setEnabled(true);
    if (!photoLineEdit->isEnabled()) photoLineEdit->setEnabled(true);
    if (row > 0)
    {
        nameLineEdit->setText(QString::fromStdString(services.GetRepo()[row - 1].GetName()));
        ageSpinBox->setValue(services.GetRepo()[row - 1].GetAge());
        breedLineEdit->setText(QString::fromStdString(services.GetRepo()[row - 1].GetBreed()));
        photoLineEdit->setText(QString::fromStdString(services.GetRepo()[row - 1].GetPhotograph()));
    }
}

void AdministratorWindow::openNewAddWindow()
{
    if (addWindow == nullptr)
    {
        addWindow = new AddWindow(services, undoServices, this);

        addWindow->show();
    }
    else
    {
        QMessageBox::warning(this, tr("Error!"), tr("You already have an add window open!"));
    }
}

void AdministratorWindow::updateDog()
{
    if (dogTable->currentRow() > 0)
    {
        std::shared_ptr<UpdateCommand> newCommand = std::make_shared<UpdateCommand>(services,
                                                                                    dogTable->currentRow() - 1,
                                                                                    services.GetRepo()[dogTable->currentRow() - 1],
                                                                                    nameLineEdit->text().toStdString(),
                                                                                    breedLineEdit->text().toStdString(),
                                                                                    (size_t)ageSpinBox->value(),
                                                                                    photoLineEdit->text().toStdString());
//        if (services.GetRepo()[dogTable->currentRow() - 1].GetName() !=
//            nameLineEdit->text().toStdString())
//        {
//            services.UpdateDogName(dogTable->currentRow() - 1, nameLineEdit->text().toStdString());
//            dogTable->item(dogTable->currentRow(), 0)->setText(nameLineEdit->text());
//        }

//        if ((int)services.GetRepo()[dogTable->currentRow() - 1].GetAge() !=
//            ageSpinBox->value())
//        {
//            services.UpdateDogAge(dogTable->currentRow() - 1, ageSpinBox->value());
//            dogTable->item(dogTable->currentRow(), 1)->setText(QString::number(ageSpinBox->value()));
//        }

//        if (services.GetRepo()[dogTable->currentRow() - 1].GetBreed() !=
//            breedLineEdit->text().toStdString())
//        {
//            services.UpdateDogBreed(dogTable->currentRow() - 1, breedLineEdit->text().toStdString());
//            dogTable->item(dogTable->currentRow(), 2)->setText(breedLineEdit->text());
//        }

//        if (services.GetRepo()[dogTable->currentRow() - 1].GetPhotograph() !=
//            photoLineEdit->text().toStdString())
//        {
//            services.UpdateDogPhotograph(dogTable->currentRow() - 1, photoLineEdit->text().toStdString());
//            dogTable->item(dogTable->currentRow(), 3)->setText(photoLineEdit->text());
//        }
        undoServices.ExecuteCommand(newCommand);
        dogTable->item(dogTable->currentRow(), 0)->setText(nameLineEdit->text());
        dogTable->item(dogTable->currentRow(), 1)->setText(QString::number(ageSpinBox->value()));
        dogTable->item(dogTable->currentRow(), 2)->setText(breedLineEdit->text());
        dogTable->item(dogTable->currentRow(), 3)->setText(photoLineEdit->text());
    }

}

void AdministratorWindow::undo()
{
    try
    {
        undoServices.Undo();

        dogTable->clear();
        QTableWidgetItem *name = new QTableWidgetItem("Name");
        QTableWidgetItem *age = new QTableWidgetItem("Age");
        QTableWidgetItem *breed = new QTableWidgetItem("Breed");
        QTableWidgetItem *photo = new QTableWidgetItem("Photograph");

        dogTable->setItem(0, 0, name);
        dogTable->setItem(0, 1, age);
        dogTable->setItem(0, 2, breed);
        dogTable->setItem(0, 3, photo);

        for (size_t i = 0; i < services.GetRepo().GetSize(); ++i)
        {
            QTableWidgetItem *dogName = new QTableWidgetItem(QString::fromStdString(services.GetRepo()[i].GetName()));
            QTableWidgetItem *dogAge = new QTableWidgetItem(QString::fromStdString(std::to_string(services.GetRepo()[i].GetAge())));
            QTableWidgetItem *dogBreed = new QTableWidgetItem(QString::fromStdString(services.GetRepo()[i].GetBreed()));
            QTableWidgetItem *dogPhoto = new QTableWidgetItem(QString::fromStdString(services.GetRepo()[i].GetPhotograph()));

            dogTable->setItem(i + 1, 0, dogName);
            dogTable->setItem(i + 1, 1, dogAge);
            dogTable->setItem(i + 1, 2, dogBreed);
            dogTable->setItem(i + 1, 3, dogPhoto);
        }
    }
    catch (UndoException& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
    }
}

void AdministratorWindow::redo()
{
    try
    {
        undoServices.Redo();

        dogTable->clear();
        QTableWidgetItem *name = new QTableWidgetItem("Name");
        QTableWidgetItem *age = new QTableWidgetItem("Age");
        QTableWidgetItem *breed = new QTableWidgetItem("Breed");
        QTableWidgetItem *photo = new QTableWidgetItem("Photograph");

        dogTable->setItem(0, 0, name);
        dogTable->setItem(0, 1, age);
        dogTable->setItem(0, 2, breed);
        dogTable->setItem(0, 3, photo);

        for (size_t i = 0; i < services.GetRepo().GetSize(); ++i)
        {
            QTableWidgetItem *dogName = new QTableWidgetItem(QString::fromStdString(services.GetRepo()[i].GetName()));
            QTableWidgetItem *dogAge = new QTableWidgetItem(QString::fromStdString(std::to_string(services.GetRepo()[i].GetAge())));
            QTableWidgetItem *dogBreed = new QTableWidgetItem(QString::fromStdString(services.GetRepo()[i].GetBreed()));
            QTableWidgetItem *dogPhoto = new QTableWidgetItem(QString::fromStdString(services.GetRepo()[i].GetPhotograph()));

            dogTable->setItem(i + 1, 0, dogName);
            dogTable->setItem(i + 1, 1, dogAge);
            dogTable->setItem(i + 1, 2, dogBreed);
            dogTable->setItem(i + 1, 3, dogPhoto);
        }
    }
    catch (RedoException& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
    }
}

void AdministratorWindow::deleteAddWindow(QString name, int age, QString breed, QString photograph)
{
    if (name != "" && age != -1 && breed != "" && photograph != "")
    {
        dogTable->clear();
        QTableWidgetItem *name = new QTableWidgetItem("Name");
        QTableWidgetItem *age = new QTableWidgetItem("Age");
        QTableWidgetItem *breed = new QTableWidgetItem("Breed");
        QTableWidgetItem *photo = new QTableWidgetItem("Photograph");

        dogTable->setItem(0, 0, name);
        dogTable->setItem(0, 1, age);
        dogTable->setItem(0, 2, breed);
        dogTable->setItem(0, 3, photo);

        for (size_t i = 0; i < services.GetRepo().GetSize(); ++i)
        {
            QTableWidgetItem *dogName = new QTableWidgetItem(QString::fromStdString(services.GetRepo()[i].GetName()));
            QTableWidgetItem *dogAge = new QTableWidgetItem(QString::fromStdString(std::to_string(services.GetRepo()[i].GetAge())));
            QTableWidgetItem *dogBreed = new QTableWidgetItem(QString::fromStdString(services.GetRepo()[i].GetBreed()));
            QTableWidgetItem *dogPhoto = new QTableWidgetItem(QString::fromStdString(services.GetRepo()[i].GetPhotograph()));

            dogTable->setItem(i + 1, 0, dogName);
            dogTable->setItem(i + 1, 1, dogAge);
            dogTable->setItem(i + 1, 2, dogBreed);
            dogTable->setItem(i + 1, 3, dogPhoto);
        }
    }

    delete addWindow;
    addWindow = nullptr;
}

void AdministratorWindow::removeDog()
{
    if (dogTable->currentRow() > 0)
    {
        std::shared_ptr<RemoveCommand> newCommand = std::make_shared<RemoveCommand>(services,
                                                                                    services.GetRepo()[dogTable->currentRow() - 1],
                                                                                    dogTable->currentRow() - 1);
        undoServices.ExecuteCommand(newCommand);
        dogTable->removeRow(dogTable->currentRow());
    }
    loadDogAttributes(dogTable->currentRow());
}

void AdministratorWindow::InitializeTable()
{
    dogTable = new QTableWidget(mainWidget);
    dogTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dogTable->setRowCount(services.GetRepo().GetSize() + 1);
    dogTable->setColumnCount(4);
    dogTable->setColumnWidth(0, mainWidget->width() / 4);
    dogTable->setColumnWidth(1, mainWidget->width() / 4);
    dogTable->setColumnWidth(2, mainWidget->width() / 4);
    dogTable->setColumnWidth(3, mainWidget->width() / 4);

    QTableWidgetItem *name = new QTableWidgetItem("Name");
    QTableWidgetItem *age = new QTableWidgetItem("Age");
    QTableWidgetItem *breed = new QTableWidgetItem("Breed");
    QTableWidgetItem *photo = new QTableWidgetItem("Photograph");

    dogTable->setItem(0, 0, name);
    dogTable->setItem(0, 1, age);
    dogTable->setItem(0, 2, breed);
    dogTable->setItem(0, 3, photo);

    for (size_t i = 0; i < services.GetRepo().GetSize(); ++i)
    {
        QTableWidgetItem *dogName = new QTableWidgetItem(QString::fromStdString(services.GetRepo()[i].GetName()));
        QTableWidgetItem *dogAge = new QTableWidgetItem(QString::fromStdString(std::to_string(services.GetRepo()[i].GetAge())));
        QTableWidgetItem *dogBreed = new QTableWidgetItem(QString::fromStdString(services.GetRepo()[i].GetBreed()));
        QTableWidgetItem *dogPhoto = new QTableWidgetItem(QString::fromStdString(services.GetRepo()[i].GetPhotograph()));

        dogTable->setItem(i + 1, 0, dogName);
        dogTable->setItem(i + 1, 1, dogAge);
        dogTable->setItem(i + 1, 2, dogBreed);
        dogTable->setItem(i + 1, 3, dogPhoto);
    }
}

void AdministratorWindow::InitializeEditBox()
{
    editGroupBox = new QGroupBox("Dog Attributes", mainWidget);
    nameLineEdit = new QLineEdit();
    ageSpinBox = new QSpinBox();
    breedLineEdit = new QLineEdit();
    photoLineEdit = new QLineEdit();
    addButton = new QPushButton("Add new dog");
    removeButton = new QPushButton("Remove dog");
    updateButton = new QPushButton("Update attributes");

    QFile file("../KeepCalmAndAdoptAPet_V4/Stylesheets/AdminButton.qss");
    file.open(QFile::ReadOnly);
    QString str = file.readAll();
    addButton->setStyleSheet(str);
    removeButton->setStyleSheet(str);
    updateButton->setStyleSheet(str);
    file.close();

    editLayout = new QFormLayout();

    editLayout->addRow(tr("&Name:"), nameLineEdit);
    editLayout->addRow(tr("&Age:"), ageSpinBox);
    editLayout->addRow(tr("&Breed:"), breedLineEdit);
    editLayout->addRow(tr("&Photograph:"), photoLineEdit);
    editLayout->addRow(addButton);
    editLayout->addRow(removeButton);
    editLayout->addRow(updateButton);

    editGroupBox->setLayout(editLayout);

    nameLineEdit->setEnabled(false);
    ageSpinBox->setEnabled(false);
    breedLineEdit->setEnabled(false);
    photoLineEdit->setEnabled(false);
}

void AdministratorWindow::InitializeUndoRedoLayout()
{
    undoRedoLayout = new QHBoxLayout();

    InitializeUndoRedoButtons();
    undoRedoLayout->addWidget(undoButton);
    undoRedoLayout->addWidget(redoButton);
}

void AdministratorWindow::InitializeUndoRedoButtons()
{
    undoButton = new QPushButton("Undo last action", this);
    redoButton = new QPushButton("Redo last action", this);

    QFile file("../KeepCalmAndAdoptAPet_V4/Stylesheets/AdminButton.qss");
    file.open(QFile::ReadOnly);
    QString str = file.readAll();

    undoButton->setStyleSheet(str);
    redoButton->setStyleSheet(str);

    file.close();
}

void AdministratorWindow::InitializeShortcuts()
{
    QShortcut *undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
    shortcuts.push_back(undoShortcut);

    QShortcut *redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
    shortcuts.push_back(redoShortcut);
}


void AdministratorWindow::InitializeButton()
{
    exitButton = new QPushButton(tr("Exit Window"));

    QFile file("../KeepCalmAndAdoptAPet_V4/Stylesheets/AdminButton.qss");
    file.open(QFile::ReadOnly);
    QString str = file.readAll();
    exitButton->setStyleSheet(str);
    file.close();
}
