#include "filesystemcustommodel.h"

FileSystemCustomModel::FileSystemCustomModel()
{

}
/*!
 * \brief adds checkboxes for first column only (read data)
 * \param index
 * \param role
 * \return
 */
QVariant FileSystemCustomModel::data(const QModelIndex &index, int role) const
{
    if (role==Qt::CheckStateRole && index.column()==0)
        return checklist.contains(index)?Qt::Checked :Qt::Unchecked;
    return QFileSystemModel::data(index,role);
}

/*!
 * \brief checks back the selected files from persistance
 * \param index
 * \param value
 * \param role
 * \return
 */
bool FileSystemCustomModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role==Qt::CheckStateRole) {
        if(value==Qt::Checked)checklist.insert(index);
        else checklist.remove(index);
        emit dataChanged(index,index);
        return true;
    }
    return QFileSystemModel::setData(index,value,role);
}

Qt::ItemFlags FileSystemCustomModel::flags(const QModelIndex &index) const
{
    return QFileSystemModel::flags(index)|Qt::ItemIsUserCheckable;
}

void FileSystemCustomModel::iterate(const QModelIndex &index, const QAbstractItemModel *model, const std::function<void (const QModelIndex &, int)> &fun, int depth)
{
    if(index.isValid())
        fun(index,depth);
    if(!model->hasChildren(index)||(index.flags()& Qt::ItemNeverHasChildren)) return;
    auto rows = model->rowCount(index);
    auto cols = model->columnCount(index);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            iterate(model->index(i,j,index),model,fun,depth+1);
        }
    }
}

QSet<QModelIndex> FileSystemCustomModel::getSelectedIndexs()
{
    return checklist;
}


//TODO: move to separate services lib
