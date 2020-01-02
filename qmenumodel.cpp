#include "qmenumodel.h"

QMenuModel::QMenuModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    slist.append(QVariant(1.0f));
    slist.append(QVariant(2.1));
    slist.append(QVariant(3));
    slist.append(QVariant(-4.868765));
    slist.append(QVariant(+1.5E3));

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Timeout()));
    timer->start(500);
}

void QMenuModel::Timeout()
{
    for(int i=0; i<slist.count(); ++i)
    {
        QMetaType::Type t=(QMetaType::Type)slist[i].type();
        switch(t)
        {
        default: break;
        case QMetaType::Int: slist[i]=slist.at(i).toInt()+1; break;
        case QMetaType::Float: slist[i]=slist.at(i).toFloat()+1.0; break;
        case QMetaType::Double: slist[i]=slist.at(i).toDouble()+1.0; break;
        }
    }
    QModelIndex topLeft=index(0, 0);
    QModelIndex bottomRight=index(slist.count()-1, 0);
    QVector<int> roles;
    roles.append((int)Qt::DisplayRole);
    emit dataChanged(topLeft, bottomRight, roles);

}

QModelIndex QMenuModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if(0!=column) return QModelIndex();
    if(row>=slist.count()) return QModelIndex();
    return this->createIndex(row, 0, row);
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
    return 1;
}

QVariant QMenuModel::data(const QModelIndex &index, int role) const
{
    if(false==index.isValid())
        return QVariant();
    if(0!=index.column())
        return QVariant();
    if(slist.count()<=index.row())
        return QVariant();

    switch(role)
    {
    default: return QVariant();
    case Qt::DisplayRole: return slist[index.row()].toString();
    }
}
