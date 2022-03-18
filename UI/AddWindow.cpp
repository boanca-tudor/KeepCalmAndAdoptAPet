#include "UI/AddWindow.h"
#include <QMessageBox>

AddWindow::AddWindow(AdminServices &services, UndoServices &undoServices, QWidget *parent) :
    QMainWindow(parent),
    services {services},
    undoServices {undoServices},
    mainWidget {new QWidget(this)},
    nameLE {new QLineEdit(mainWidget)},
    ageSB {new QSpinBox(mainWidget)},
    breedLE {new QLineEdit(mainWidget)},
    photographLE {new QLineEdit(mainWidget)},
    addButton {new QPushButton("Add dog")},
    attributesLayout {new QFormLayout()},
    mainLayout {new QVBoxLayout(mainWidget)}
{
    attributesLayout->addRow("&Name", nameLE);
    attributesLayout->addRow("&Age", ageSB);
    attributesLayout->addRow("&Breed", breedLE);
    attributesLayout->addRow("&Photograph", photographLE);
    attributesLayout->addRow(addButton);

    mainLayout->addLayout(attributesLayout);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    ConnectSignalsAndSlots(parent);
}

void AddWindow::closeEvent(QCloseEvent *e)
{
    QMainWindow::closeEvent(e);
    if (breedLE->text() != "" && nameLE->text() != "" && ageSB->value() > 0 && photographLE->text() != "")
        emit closeWindow(nameLE->text(), ageSB->value(), breedLE->text(), photographLE->text());
    else
        emit closeWindow("", 0, "", "");
}

void AddWindow::ConnectSignalsAndSlots(QWidget* parent)
{
    connect(addButton, SIGNAL(clicked()), this, SLOT(AddNewDog()));
    connect(this, SIGNAL(closeWindow(QString, int, QString, QString)), parent, SLOT(deleteAddWindow(QString, int, QString, QString)));
}

void AddWindow::AddNewDog()
{
    try
    {
        std::shared_ptr<AddCommand> newCommand = std::make_shared<AddCommand>(services,
                                                                              nameLE->text().toStdString(),
                                                                              breedLE->text().toStdString(),
                                                                              (size_t)ageSB->value(),
                                                                              photographLE->text().toStdString());

        undoServices.ExecuteCommand(newCommand);

        QMessageBox::information(this, tr("Done"), tr("Dog succesfully added!"));

        close();
    }
    catch (ValidatorException& ex)
    {
        QMessageBox::critical(this, tr("Error!"), tr(ex.what()));
    }
}
