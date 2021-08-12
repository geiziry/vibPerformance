#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dockWidget->setAttribute(Qt::WA_WState_ExplicitShowHide);
    connect(ui->actionOpen,&QAction::triggered,ui->sgyfiles,&sgyFileSelection::setRootDir);
    connect(ui->sgyfiles,&sgyFileSelection::processSelectedIndexs,
            ui->sgyPlot,&plotArea::openSelectedSgyFiles);
    //pass points of selected sgyfiles to plot spectrum
    connect(ui->sgyPlot,&plotArea::calcSpectrum,ui->specPlot,&spectrumCalc::processSpecCalc);
    connect(ui->sgyPlot,&plotArea::setTraceIndexRange,ui->trNoSpin,&QSpinBox::setRange);
    connect(ui->trNoSpin,QOverload<int>::of(&QSpinBox::valueChanged), ui->sgyPlot, &plotArea::plotTraceIndex);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//TODO: move to separate gui lib
