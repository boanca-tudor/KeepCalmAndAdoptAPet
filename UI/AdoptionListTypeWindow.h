#ifndef ADOPTIONLISTTYPEWINDOW_H
#define ADOPTIONLISTTYPEWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QFormLayout>
#include <QPushButton>
#include "Business/UserServices.h"

class AdoptionListTypeWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AdoptionListTypeWindow(UserServices& services, QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent* e) override;
private:
    void ConnectSignalsAndSlots(QObject* parent);

    void InitializeLayout();
    UserServices& services;
    QWidget* mainWidget;
    QFormLayout* mainLayout;
    QRadioButton* htmlRB;
    QRadioButton* csvRB;
    QRadioButton* inAppRB;

    QPushButton* selectButton;

public slots:
    void selectType();
signals:
    void closeWindow(QString);
};

#endif // ADOPTIONLISTTYPEWINDOW_H
