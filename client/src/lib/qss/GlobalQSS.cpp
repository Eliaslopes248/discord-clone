#include "../../../include/lib/ui/GlobalQSS.h"
#include <QColor>
#include <QGraphicsDropShadowEffect>
#include <QWidget>

void setBoxShadow(QWidget* widget, QColor color, int blur, int xOffSet, int yOffSet)
{
    auto* shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(blur);
    shadow->setOffset(xOffSet, yOffSet);   // X, Y offset
    shadow->setColor(color);

    widget->setGraphicsEffect(shadow);
}
