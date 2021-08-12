#include "crosscor.h"
#include "ui_crosscor.h"

crossCor::crossCor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::crossCor)
{
    ui->setupUi(this);
}

crossCor::~crossCor()
{
    delete ui;
}
