#ifndef DISPLAYFORMAT_H
#define DISPLAYFORMAT_H

#include <QPixmap>

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkSobelEdgeDetectionImageFilter.h>

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

QPixmap EdgeDetection(const QPixmap &image);
};
#endif // DISPLAYFORMAT_H
