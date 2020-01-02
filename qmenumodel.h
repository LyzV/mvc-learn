#ifndef QMENUMODEL_H
#define QMENUMODEL_H

#include <QAbstractItemModel>
#include <QString>
#include <QVariant>
#include <QList>
#include <QTimer>

class QMenuModel : public QAbstractItemModel
{
    Q_OBJECT

    typedef struct
    {
        QString Name;
        QVariant Value;
        QString Unit;
    } SMenuStr;

    QList<SMenuStr> slist;
    QTimer *timer=nullptr;

public:
    QMenuModel(QObject *parent = 0);
private slots:
    void Timeout(void);

public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // QMENUMODEL_H
