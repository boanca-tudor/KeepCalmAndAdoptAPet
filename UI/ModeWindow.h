#ifndef MODEWINDOW_H
#define MODEWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "Business/AdminServices.h"
#include "Business/UserServices.h"
#include "Business/undoservices.h"
#include "UI/AdministratorWindow.h"
#include "UI/UserWindow.h"
#include "UI/Charts/DogChart.h"

class ModeWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ModeWindow(AdminServices& adminServices, UserServices& userServices, UndoServices& undoServices, QWidget *parent = nullptr);

    ~ModeWindow();
private:
    void ConnectSignalsAndSlots();

    void InitializeButton(QPushButton* button);
    void InitializeImageLabel(QLabel* label, QString path);

    AdminServices& adminServices;
    UserServices& userServices;
    UndoServices& undoServices;

    QWidget* mainWidget;
    AdministratorWindow* adminWindow;
    UserWindow* userWindow;
    DogChart* chartWindow;

    QVBoxLayout* layout;
    QPushButton* userButton;
    QPushButton* adminButton;
    QPushButton* chartButton;

    QLabel* imageLabel;
    QImage image;
public slots:
    void DeleteAdminWindow();
    void DeleteUserWindow();
    void DeleteChartWindow();

    void OpenAdminWindow();
    void OpenUserWindow();
    void OpenChartWindow();

};

#endif // MODEWINDOW_H
