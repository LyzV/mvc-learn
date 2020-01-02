#include "qmenumodel.h"

QMenuModel::QMenuModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    SMenuStr mstr;

    mstr.Name="First"; mstr.Value=QVariant(1.0f); mstr.Unit="MPa"; slist.append(mstr);
    mstr.Name="Second"; mstr.Value=QVariant(2.1f); mstr.Unit="KPa"; slist.append(mstr);
    mstr.Name="Third"; mstr.Value=QVariant(3); mstr.Unit="At"; slist.append(mstr);
    mstr.Name="Forth"; mstr.Value=QVariant(-4.934857); mstr.Unit="Atm"; slist.append(mstr);
    mstr.Name="Fifth"; mstr.Value=QVariant(+1.534E2); mstr.Unit="psi"; slist.append(mstr);

//    QModelIndex topLeft=index(0, 0);
//    QModelIndex bottomRight=index(slist.count()-1, 2);
//    QVector<int> roles;
//    roles.append((int)Qt::DisplayRole);
//    emit dataChanged(topLeft, bottomRight, roles);

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Timeout()));
    timer->start(500);
}

void QMenuModel::Timeout()
{
    for(int i=0; i<slist.count(); ++i)
    {
        QMetaType::Type t=(QMetaType::Type)slist[i].Value.type();
        switch(t)
        {
        default: break;
        case QMetaType::Int: slist[i].Value=slist.at(i).Value.toInt()+1; break;
        case QMetaType::Float: slist[i].Value=slist.at(i).Value.toFloat()+1.0; break;
        case QMetaType::Double: slist[i].Value=slist.at(i).Value.toDouble()+1.0; break;
        }
    }
    QModelIndex topLeft=index(0, 1);
    QModelIndex bottomRight=index(slist.count()-1, 1);
    QVector<int> roles;
    roles.append((int)Qt::DisplayRole);
    emit dataChanged(topLeft, bottomRight, roles);

}

QModelIndex QMenuModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if(3<=column) return QModelIndex();
    if(row>=slist.count()) return QModelIndex();
    return this->createIndex(row, column, row);
}

QModelIndex QMenuModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

int QMenuModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return slist.count();
}

int QMenuModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant QMenuModel::data(const QModelIndex &index, int role) const
{
    if(false==index.isValid())
        return QVariant();
    if(slist.count()<=index.row())
        return QVariant();

    if(0==index.column())
    {
        switch(role)
        {
        default: return QVariant();
        case Qt::DisplayRole: return slist[index.row()].Name;
        }
    }
    else if(1==index.column())
    {
        switch(role)
        {
        default: return QVariant();
        case Qt::DisplayRole: return slist[index.row()].Value.toString();
        }
    }
    else if(2==index.column())
    {
        switch(role)
        {
        default: return QVariant();
        case Qt::DisplayRole: return slist[index.row()].Unit;
        }
    }
    else
        return QVariant();

}
