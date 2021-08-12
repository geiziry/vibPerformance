#ifndef UTILS_H
#define UTILS_H

#include <QWidget>

namespace shared {
float roundToThousandths(float x);
QWidget* parentByName(QWidget* widget, QString name);
}

#endif // UTILS_H
