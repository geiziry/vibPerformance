#include <QtTest>
#include <QCoreApplication>
#include <QUrl>
#include "data.h"
#include "mainwindow.h"
#include "filesystemcustommodel.h"
#include "ui_mainwindow.h"
#include "ui_sgyfileselection.h"

using namespace Segy;

class open_sgy_ui : public QObject
{
    Q_OBJECT

public:
    open_sgy_ui(QObject* parent=nullptr);
    ~open_sgy_ui();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_ui();
    void test_model();
    void TimeOut();
private:
    QString m_curr_path;
    QString m_testdata_path;
    MainWindow *m_mainWindow;
};

open_sgy_ui::open_sgy_ui(QObject *parent):
    QObject(parent),
    m_curr_path(QDir::currentPath())
{
    QTestEventLoop::instance().enterLoop(1);
}

open_sgy_ui::~open_sgy_ui()
{
}

void open_sgy_ui::initTestCase()
{
    m_mainWindow=new MainWindow();
    QApplication::setActiveWindow(m_mainWindow);
    m_testdata_path=m_curr_path+"/../sgytest/testdata/";
}

void open_sgy_ui::cleanupTestCase()
{

}


void open_sgy_ui::test_ui()
{
    QAction* actionOpen=m_mainWindow->findChild<QAction*>("actionOpen");
    QVERIFY(actionOpen);
    m_mainWindow->show();
    QVERIFY(QTest::qWaitForWindowExposed(m_mainWindow));
    QVERIFY(m_mainWindow->isVisible());
    QSignalSpy stateSpy(actionOpen,&QAction::triggered);
    QVERIFY(stateSpy.isValid());
    QCOMPARE(stateSpy.count(),0);

    QTimer::singleShot(100,this,SLOT(TimeOut()));
    QTest::keyClick(m_mainWindow,Qt::Key_O,Qt::ControlModifier);
    QTest::keyClick(m_mainWindow,Qt::Key_Enter);
    QCOMPARE(stateSpy.count(),1);
    test_model();
}

void open_sgy_ui::test_model()
{
    auto model=m_mainWindow->ui->sgyfiles->Model();
    auto tree=m_mainWindow->ui->sgyfiles->ui->tree;
    model->index(m_testdata_path);
    QVERIFY(m_mainWindow->ui->sgyfiles->ui->tree->rootIsDecorated());
    QDir testdir(m_testdata_path);

    foreach (QFileInfo fileInfo, testdir.entryInfoList()) {
        if (!fileInfo.isDir() && fileInfo.fileName().contains("Run")){
            auto idx=model->index(fileInfo.filePath());
            m_mainWindow->ui->sgyfiles->ui->
                    tree->selectionModel()->
                    select(idx,QItemSelectionModel::Select|QItemSelectionModel::Rows);
        }
    }
    tree->expandAll();
    const QModelIndex index = tree->selectionModel()->currentIndex();
    QString selectedText = index.data(Qt::DisplayRole).toString();
    auto indexes=model->getSelectedIndexs();
    m_mainWindow->ui->sgyfiles->getSelectedIndexs();

}

void open_sgy_ui::TimeOut()
{
    QWidgetList allToplevelWidgets=QApplication::topLevelWidgets();
    foreach (QWidget *w, allToplevelWidgets) {
        if (w->inherits("QDialog")) {
            QFileDialog *dialog=qobject_cast<QFileDialog*>(w);
            QTest::keyClick(dialog,Qt::Key_Enter);
        }
    }
}

QTEST_MAIN(open_sgy_ui)

#include "tst_open_sgy_ui.moc"
