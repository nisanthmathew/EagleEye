#ifndef EEQRUBBERBAND_H
#define EEQRUBBERBAND_H

#include <QPen>
#include <QRubberBand>

namespace EagleEye
{
class EEROIQRubberBand : public QRubberBand
{
    Q_OBJECT
public:
    explicit EEROIQRubberBand(Shape shape, QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *event) override;
    QPen SetupROIPen();

    QPen m_ROIPen;
};
}
#endif // EEQRUBBERBAND_H
