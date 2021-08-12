#ifndef CROSSCOR_H
#define CROSSCOR_H

#include <QWidget>

namespace Ui {
class crossCor;
}

class crossCor : public QWidget
{
    Q_OBJECT

public:
    explicit crossCor(QWidget *parent = nullptr);
    ~crossCor();

private:
    Ui::crossCor *ui;
};

#endif // CROSSCOR_H
