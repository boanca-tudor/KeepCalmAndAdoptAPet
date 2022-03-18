#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include "Business/AdminServices.h"
#include "Business/undoservices.h"

class AddWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AddWindow(AdminServices& services, UndoServices& undoServices, QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent* e) override;
private:
    void ConnectSignalsAndSlots(QWidget* parent);
    void InitializeButton();

    AdminServices& services;
    UndoServices& undoServices;

    QWidget *mainWidget;
    QLineEdit *nameLE;
    QSpinBox *ageSB;
    QLineEdit *breedLE;
    QLineEdit *photographLE;
    QPushButton *addButton;

    QFormLayout *attributesLayout;
    QVBoxLayout *mainLayout;
public slots:
    void AddNewDog();
signals:
    void closeWindow(QString, int, QString, QString);
};

#endif // ADDWINDOW_H
