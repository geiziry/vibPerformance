#ifndef SGYFILESELECTION_H
#define SGYFILESELECTION_H

#include <QWidget>

class FileSystemCustomModel;
namespace Ui {
class sgyFileSelection;
}

class sgyFileSelection : public QWidget
{
    Q_OBJECT

    friend class open_sgy_ui;

public:
    explicit sgyFileSelection(QWidget *parent = nullptr);
    ~sgyFileSelection();
    FileSystemCustomModel* Model();
signals:
    void processSelectedIndexs(QStringList indexes);
public slots:
    void setRootDir();
    void getSelectedIndexs();

private:
    void initModel();
    Ui::sgyFileSelection *ui;
    QString rootDir;
    FileSystemCustomModel *m_model;
};

#endif // SGYFILESELECTION_H
