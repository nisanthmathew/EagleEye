#ifndef DISPLAYFORMAT_H
#define DISPLAYFORMAT_H

#include "imageprocessingutilities.h"

#include <QPixmap>

namespace EagleEye
{

enum DisplayFormats
{
    GreyScale = 0,
    Edge,
    Original
};

QPixmap ConvertRGBToGreyScale(const QPixmap &image);
QPixmap ConvertRGBToEdges(const QPixmap &image);
};
#endif // DISPLAYFORMAT_H
