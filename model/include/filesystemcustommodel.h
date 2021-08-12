#ifndef FILESYSTEMCUSTOMMODEL_H
#define FILESYSTEMCUSTOMMODEL_H

#include <QFileSystemModel>
#include <QSet>


class FileSystemCustomModel : public QFileSystemModel
{
public:
    FileSystemCustomModel();



    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void iterate(const QModelIndex& index,const QAbstractItemModel *model,
                 const std::function<void(const QModelIndex&, int)> &fun, int depth=0);
    QSet<QModelIndex> getSelectedIndexs();
private:
    QSet<QModelIndex> checklist;
};

#endif // FILESYSTEMCUSTOMMODEL_H
