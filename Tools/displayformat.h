#ifndef DISPLAYFORMAT_H
#define DISPLAYFORMAT_H

#include <QPixmap>


namespace EagleEye
{
enum DisplayFormats{
    GreyScale = 0,
    Original
};

QPixmap ConvertRGBToGreyScale(const QPixmap &image);
}
#endif // DISPLAYFORMAT_H