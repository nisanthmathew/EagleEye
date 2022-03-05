#ifndef ITKUTILITIES_H
#define ITKUTILITIES_H

#include <QPixmap>

#include <itkImage.h>
#include <itkRGBPixel.h>


namespace EagleEye
{

using EERGBPixelType = itk::RGBPixel<unsigned char>;
using EERGBImageType = itk::Image<EERGBPixelType, 2>;

using EEPixelType = float;
using EEImageType = itk::Image<EEPixelType, 2>;
EERGBImageType::Pointer ITKImageFromPixmap(const QPixmap &qPixmap);
QImage QImageFromITKImage(const EERGBImageType::Pointer itkImage);
};
#endif // ITKUTILITIES_H
