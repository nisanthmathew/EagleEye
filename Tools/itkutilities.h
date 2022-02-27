#ifndef ITKUTILITIES_H
#define ITKUTILITIES_H

#include <QPixmap>

#include <itkImage.h>


namespace EagleEye
{
using EEPixelType = float;
using EEImageType = itk::Image<EEPixelType, 2>;
EEImageType::Pointer ITKImageFromPixmap(const QPixmap &qPixmap);
QPixmap PixmapFromITKImage(const EEImageType::Pointer itkImage);
};
#endif // ITKUTILITIES_H
