#ifndef DISPLAYFORMAT_H
#define DISPLAYFORMAT_H

#include <QPixmap>

namespace EagleEye
{

enum class DisplayFormats
{
    GreyScale = 0,
    Edge,
    Original
};

QPixmap ConvertRGBToGreyScale(const QPixmap &image);
QPixmap ConvertRGBToEdges(const QPixmap &image);
QPixmap CombineROIAndDisplayedPixmap(const QPixmap &roiPixmap, const QPixmap &displayedPixmap, int startX, int startY);
}
#endif // DISPLAYFORMAT_H
