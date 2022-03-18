#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <QMainWindow>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include "Business/UserServices.h"

class FilterWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit FilterWindow(UserServices& services, QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent* e) override;
private:
    void ConnectSignalsAndSlots(QWidget* parent);
    void InitializeLayout();

    UserServices& services;

    QWidget* mainWidget;
    QFormLayout* mainLayout;
    QLineEdit* breedLE;
    QSpinBox* ageSB;
    QPushButton* filterButton;
public slots:
    void Filter();
signals:
    void closeWindow(QString, int);
};

#endif // FILTERWINDOW_H
