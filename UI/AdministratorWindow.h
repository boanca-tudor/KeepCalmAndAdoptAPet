#ifndef ADMINISTRATORWINDOW_H
#define ADMINISTRATORWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTableWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QShortcut>
#include "Business/AdminServices.h"
#include "Business/undoservices.h"
#include "UI/AddWindow.h"

class AdministratorWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AdministratorWindow(AdminServices& services, UndoServices& undoServices, QWidget *parent = nullptr);

    ~AdministratorWindow();

protected:
    void closeEvent(QCloseEvent* e) override;
private:
    void ConnectSignalsAndSlots(QWidget* parent);
    void InitializeButton();
    void InitializeTable();
    void InitializeEditBox();
    void InitializeUndoRedoLayout();
    void InitializeUndoRedoButtons();
    void InitializeShortcuts();

    AdminServices& services;
    UndoServices& undoServices;

    QWidget* mainWidget;
    QVBoxLayout* layout;

    QTableWidget* dogTable;

    QGroupBox* editGroupBox;
    QFormLayout* editLayout;
    QLineEdit* nameLineEdit;
    QSpinBox* ageSpinBox;
    QLineEdit* breedLineEdit;
    QLineEdit* photoLineEdit;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* updateButton;

    QHBoxLayout* undoRedoLayout;
    QPushButton* undoButton;
    QPushButton* redoButton;

    QPushButton* exitButton;

    QList<QShortcut*> shortcuts;

    AddWindow* addWindow;
public slots:
    void closeWindow();

    void loadDogAttributes(int row);

    void openNewAddWindow();

    void removeDog();

    void updateDog();

    void undo();

    void redo();

    void deleteAddWindow(QString, int, QString, QString);
signals:
    void windowClosed();
};

#endif // ADMINISTRATORWINDOW_H
