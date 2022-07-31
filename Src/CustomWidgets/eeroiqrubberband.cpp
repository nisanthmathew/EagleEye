#include "eeroiqrubberband.h"

#include <QPaintEvent>
#include <QPainter>

EEROIQRubberBand::EEROIQRubberBand(Shape shape, QWidget *parent)
    : QRubberBand(shape, parent)
{
    m_ROIPen = SetupROIPen();
}

void EEROIQRubberBand::EEROIQRubberBand::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor brush_color = QColor(Qt::transparent); //Transparent background
    painter.setBrush(QBrush(brush_color));
    painter.setPen(m_ROIPen);
    painter.drawRect(event->rect());
}

QPen EEROIQRubberBand::SetupROIPen()
{
    QPen ROIPen;
    ROIPen.setColor(QColor(250, 189, 17));
    QVector<qreal> dashes;
    const qreal space = 4;
    const qreal line = 4;
    dashes << line << space << line << space << line << space << line << space << line << space;
    ROIPen.setDashPattern(dashes);
    ROIPen.setWidth(4);
    return ROIPen;
}
