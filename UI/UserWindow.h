#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include "Business/UserServices.h"
#include "UI/FilterWindow.h"
#include "UI/AdoptionListTypeWindow.h"
#include "UI/adoptionlistviewer.h"

class UserWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit UserWindow(UserServices& services, QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent* e) override;
private:
    void ConnectSignalsAndSlots(QWidget* parent);

    void InitializeButton(QPushButton* button);
    void InitializeLineEdit(QLineEdit* lineEdit);

    void InitializeBottomButtonLayout();

    void InitializeAttributesBox();
    void InitializeAttributesLayout();
    void InitializeAdoptionButtonsLayout();

    UserServices& services;

    QWidget* mainWidget;
    QVBoxLayout* mainLayout;

    QGroupBox* attributesBox;

    QLineEdit* nameLE;
    QLineEdit* ageLE;
    QLineEdit* breedLE;
    QPushButton* viewPhotoButton;
    QFormLayout* attributesLayout;

    QPushButton* adoptButton;
    QPushButton* nextButton;
    QHBoxLayout* adoptionButtonsLayout;

    QPushButton* startButton;
    QPushButton* filterButton;
    QPushButton* stopButton;
    QPushButton* viewAdoptionListButton;
    QHBoxLayout* buttonsLayout;

    QPushButton* exitButton;

    FilterWindow* filterWindow;
    AdoptionListTypeWindow *typeWindow;
    AdoptionListViewer *listViewer;
public slots:
    void StartIterating();

    void ViewPhoto();
    void AdoptDog();
    void SkipDog();

    void StopViewing();

    void OpenFilterWindow();
    void DeleteFilterWindow(QString, int);

    void OpenTypeWindow();
    void DeleteTypeWindow(QString);

    void openViewWindow();
    void deleteViewWindow();
signals:
    void windowClosed();
};

#endif // USERWINDOW_H
