#include "adoptionlistmodel.h"
#include <QFont>

AdoptionListModel::AdoptionListModel(const AdoptionList &list) :
    adoptionList {list}
{

}

AdoptionListModel::~AdoptionListModel()
{

}

int AdoptionListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return adoptionList.GetList().size();
}

int AdoptionListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 4;
}

QVariant AdoptionListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int column = index.column();

    // get the genes
    auto dogs = adoptionList.GetList();

    // get the gene from the current row
    Dog d = dogs[row];

    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
        case 0:
            return QString::fromStdString(d.GetName());
        case 1:
            return QString::fromStdString(d.GetBreed());
        case 2:
            return QString::number(d.GetAge());
        case 3:
            return QString::fromStdString(d.GetPhotograph());
        default:
            break;
        }
    }

    if (role == Qt::FontRole)
    {
        QFont font("Times", 15, 10, true);
        font.setItalic(false);
        return font;
    }

    return QVariant();
}

QVariant AdoptionListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString("Dog name");
            case 1:
                return QString("Dog breed");
            case 2:
                return QString("Dog age");
            case 3:
                return QString("Dog photograph");
            default:
                break;
            }
        }
    }
    if (role == Qt::FontRole)
    {
        QFont font("Times", 15, 10, true);
        font.setBold(true);
        font.setItalic(false);
        return font;
    }

    return QVariant{};
}
