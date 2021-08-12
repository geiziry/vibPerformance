#include "filesystemcustommodel.h"
#include "sgyfileselection.h"
#include "ui_sgyfileselection.h"

#include <QFileDialog>
#include <QFileSystemModel>


sgyFileSelection::sgyFileSelection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sgyFileSelection),
    m_model(new FileSystemCustomModel)
{
    ui->setupUi(this);
    connect(ui->plotBtn,&QPushButton::clicked,this,&sgyFileSelection::getSelectedIndexs);
    initModel();
}

sgyFileSelection::~sgyFileSelection()
{
    delete ui;
}

FileSystemCustomModel *sgyFileSelection::Model()
{
    return m_model;
}

/*!
 * \brief sets the root directory for the sgy files selection tree
 */
void sgyFileSelection::setRootDir()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::DirectoryOnly);
    fileDialog.setOption(QFileDialog::DontUseNativeDialog, true);
    fileDialog.setOption(QFileDialog::ShowDirsOnly, false);
    fileDialog.resize(1000,500);
    if (fileDialog.exec()){
        rootDir=fileDialog.directory().path();
        ui->tree->setRootIndex(m_model->index(rootDir));
    }
}
/*!
 * \brief gets list of files selected in the model tree
 * extracts the full path of the files,
 * and add to list which is passed as parameter in the processSelectedIndex signal
 * connected to the add sgyfiles button click signal
 */
void sgyFileSelection::getSelectedIndexs()
{
    auto selectedIndexs=m_model->getSelectedIndexs();
    QStringList paths;
    for(auto index:selectedIndexs){
        paths.append(m_model->filePath(index));
    }
    emit processSelectedIndexs(paths);
}

/*!
 * \brief initiates the file system model, and sets its root to the rootpath
 * filters out the files to be shown in the tree to extensions (.sgy, .segy) only
 */
void sgyFileSelection::initModel()
{
    m_model->setRootPath(QDir::rootPath());
    m_model->setFilter(QDir::NoDotAndDotDot|QDir::Files|QDir::AllDirs);
    QStringList filters;
    //set files filter to show sgy files only
    filters<<"*.sgy"<<"*.segy";
    m_model->setNameFilters(filters);
    m_model->setNameFilterDisables(false);
    ui->tree->setModel(m_model);
    ui->tree->setRootIndex(m_model->index(rootDir));
    ui->tree->hideColumn(1);
    ui->tree->hideColumn(2);
    ui->tree->hideColumn(3);

}
