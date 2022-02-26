#include "displayformat.h"
#include <../datahandler.h>
#include "../logger.h"

namespace EagleEye
{

QPixmap ConvertRGBToGreyScale(const QPixmap &image)
{
    QImage greyScaleImage = image.toImage().convertToFormat(QImage::Format_Grayscale8);
    QPixmap greyScalePixmap = QPixmap::fromImage(greyScaleImage);
    return greyScalePixmap;
}
}
