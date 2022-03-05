#ifndef ITKUTILITIES_H
#define ITKUTILITIES_H

#include <QImage>

#include <itkImage.h>
#include <itkRGBPixel.h>


namespace EagleEye
{


using EEPixelType = float;
using EEImageType = itk::Image<EEPixelType, 2>;
using EERGBPixelType = itk::RGBPixel<float>;
using EERGBImageType = itk::Image<EERGBPixelType, 2>;
EERGBImageType::Pointer EERGBITKImageFromQImage(const QImage &qImage);
EEImageType::Pointer EEGrayITKImageFromQImage(const QImage &qImage);

QImage EERGBQImageFromITKImage(const EERGBImageType::Pointer itkImage);
QImage EEGrayQImageFromITKImage(const EEImageType::Pointer itkImage);
};
#endif // ITKUTILITIES_H
