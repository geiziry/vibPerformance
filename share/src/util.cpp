#include "util.h"
#include <cmath>
/*!
 * \brief rounds the passed float to nearest thousands
 * \param x
 * \return rounded float to thousands
 */
float shared::roundToThousandths(float x)
{
    x /=1000;
    return floor(x + 0.5) * 1000;
}

/*!
 * \brief recursively seaches for parent with objectname
 * \param widget the starting point for search
 * \param name objectname of the parent to be found
 * \return
 */
QWidget *shared::parentByName(QWidget *widget, QString name)
{
    widget=widget->parentWidget();
    if (widget && widget->objectName() != name)
        return parentByName(widget, name);
    return widget;
}
