#include "displayformat.h"

namespace EagleEye
{
QPixmap ConvertRGBToGreyScale(const QPixmap &image)
{
    QImage greyScaleImage = image.toImage().convertToFormat(QImage::Format_Grayscale8);
    return QPixmap::fromImage(greyScaleImage);
}

QPixmap ConvertRGBToEdges(const QPixmap &image)
{
    return EEEdgeDetection(image);
}
}
