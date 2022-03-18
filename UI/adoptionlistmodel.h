#ifndef ADOPTIONLISTMODEL_H
#define ADOPTIONLISTMODEL_H

#include <QAbstractTableModel>
#include "Persistency/AdoptionList.h"

class AdoptionListModel : public QAbstractTableModel
{
public:
    explicit AdoptionListModel(const AdoptionList& list);

    virtual ~AdoptionListModel();

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

    int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
private:
    const AdoptionList& adoptionList;
};

#endif // ADOPTIONLISTMODEL_H
