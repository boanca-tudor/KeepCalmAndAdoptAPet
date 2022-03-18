#ifndef ADOPTIONLISTVIEWER_H
#define ADOPTIONLISTVIEWER_H

#include <QMainWindow>
#include <QTableView>
#include <QVBoxLayout>
#include "adoptionlistmodel.h"
#include "Persistency/AdoptionList.h"

class AdoptionListViewer : public QMainWindow
{
    Q_OBJECT
public:
    explicit AdoptionListViewer(const AdoptionList& list, QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent* e) override;
private:
    void ConnectSignalsAndSlots(QWidget* parent);

    void InitializeView();
    void InitializeLayout();
    const AdoptionList& adoptionList;

    QWidget* mainWidget;
    QVBoxLayout* mainLayout;

    QTableView* adoptionListView;
signals:
    void windowClosed();
};

#endif // ADOPTIONLISTVIEWER_H
