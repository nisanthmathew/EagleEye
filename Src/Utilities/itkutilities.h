#ifndef ITKUTILITIES_H
#define ITKUTILITIES_H

#include <QImage>

#include <itkImage.h>
#include <itkRGBPixel.h>
#include "../Singletons/logger.h"

namespace EagleEye
{

using EEFloatPixelType = float;
using EEFloatITKImageType = itk::Image<EEFloatPixelType, 2>;

using EERGBITKPixelType = itk::RGBPixel<float>;
using EERGBITKImageType = itk::Image<EERGBITKPixelType, 2>;

template<typename T>
using EEITKImageType = itk::Image<T, 2>;

template<typename T>
using EEITKImageSmartPointer = typename T::Pointer;

template<typename T>
using EEImageIndexType = typename T::IndexType;

template<typename T>
using EEImageSizeType = typename T::SizeType;

template<typename T>
using EEImageSizeType = typename T::SizeType;

template<typename T>
using EEImageRegionType = typename T::RegionType;

template<typename T>
using EEImagePixelType = typename T::PixelType;

template <typename T>
EEITKImageSmartPointer<T> EEQImageToITKImageAdapter(const QImage &qImage)
{

    EEITKImageSmartPointer<T> image = nullptr;
    EEITKImageSmartPointer<EERGBITKImageType> rgbImage  = nullptr;
    EEImageIndexType<T> start;

    start[0] = 0; // first index on X
    start[1] = 0; // first index on Y

    EEImageSizeType<T> size;
    size[0] = qImage.width(); // size along X
    size[1] = qImage.height(); // size along Y
    EagleEye::Logger::CENTRAL_LOGGER().LogMessage(
                QString("itkutilities::EEQImageToITKImageAdapter(): Input QImage image width is %1.").arg(qImage.width()),
                EagleEye::LOGLEVEL::EE_DEBUG);
    EagleEye::Logger::CENTRAL_LOGGER().LogMessage(
                QString("itkutilities::EEQImageToITKImageAdapter(): Input QImage image height is %1.").arg(qImage.height()),
                EagleEye::LOGLEVEL::EE_DEBUG);

    EEImageRegionType<T> region;
    region.SetSize(size);
    region.SetIndex(start);

    bool isRGBPixelType = (std::is_same<EEImagePixelType<T>,itk::RGBPixel<float>>::value);

    if (!isRGBPixelType)
    {
        image = T::New();
        image->SetRegions(region);
        image->Allocate();
        image->Update();

    }
    else
    {
        rgbImage = EERGBITKImageType::New();
        rgbImage->SetRegions(region);
        rgbImage->Allocate();
        rgbImage->Update();
    }

    EERGBITKPixelType rgbPixel;
    EEImageIndexType<EERGBITKImageType> rgbIndex;
    EEImagePixelType<T> inputImagePixel;
    EEImageIndexType<T> inputImageIndex;

    for (int row = 0; row < qImage.height(); row++)
    {
        QRgb *rowData = (QRgb*)qImage.scanLine(row);
        for (int col = 0; col < qImage.width(); col++)
        {
            if (isRGBPixelType)
            {
                rgbIndex[0] = col;
                rgbIndex[1] = row;
                rgbPixel.Set(qRed(rowData[col]), qGreen(rowData[col]), qBlue(rowData[col]));
                rgbImage->SetPixel(rgbIndex, rgbPixel);
            }
            else
            {
                inputImageIndex[0] = col;
                inputImageIndex[1] = row;
                inputImagePixel = (qRed(rowData[col]) + qGreen(rowData[col]) + qBlue(rowData[col])) / 3;
                image->SetPixel(inputImageIndex, inputImagePixel);
            }
        }
    }

    EagleEye::Logger::CENTRAL_LOGGER().LogMessage(
                QString("itkutilities::EEQImageToITKImageAdapter(): Output itkImage image width is %1.")
                .arg(image->GetLargestPossibleRegion().GetSize()[0]),
            EagleEye::LOGLEVEL::EE_DEBUG);
    EagleEye::Logger::CENTRAL_LOGGER().LogMessage(
                QString("itkutilities::EEQImageToITKImageAdapter(): Output itkImage image width is %1.")
                .arg(image->GetLargestPossibleRegion().GetSize()[1]),
            EagleEye::LOGLEVEL::EE_DEBUG);

    return image;
}


template <typename  T>
QImage EEITKImageToQImageAdapter(const EEITKImageSmartPointer<EEITKImageType<T>> itkImage)
{
    const auto width = itkImage->GetLargestPossibleRegion().GetSize()[0];
    const auto height = itkImage->GetLargestPossibleRegion().GetSize()[1];
    EagleEye::Logger::CENTRAL_LOGGER().LogMessage(
                QString("itkutilities::EEITKImageToQImageAdapter(): Input itkImage x spacing is %1.").arg(itkImage->GetSpacing()[0]),
            EagleEye::LOGLEVEL::EE_DEBUG);
    EagleEye::Logger::CENTRAL_LOGGER().LogMessage(
                QString("itkutilities::EEITKImageToQImageAdapter(): Input itkImage y spacing is %1.").arg(itkImage->GetSpacing()[1]),
            EagleEye::LOGLEVEL::EE_DEBUG);
    EagleEye::Logger::CENTRAL_LOGGER().LogMessage(
                QString("itkutilities::EEITKImageToQImageAdapter(): Input itkImage image width is %1.").arg(width),
                EagleEye::LOGLEVEL::EE_DEBUG);
    EagleEye::Logger::CENTRAL_LOGGER().LogMessage(
                QString("itkutilities::EEITKImageToQImageAdapter(): Input itkImage image width is %1.").arg(height),
                EagleEye::LOGLEVEL::EE_DEBUG);

    QImage qImage (QSize(width, height), QImage::Format_RGB32);
    EEImageIndexType<EEITKImageType<T>> index;

    bool isRGBPixelType = (std::is_same<T, EERGBITKPixelType>::value);

    for (int row = 0; row < height; row++)
    {
        QRgb *rowData = (QRgb*)qImage.scanLine(row);
        for (int col = 0; col < width; col++)
        {
            index[0] = col;
            index[1] = row;
            if (!isRGBPixelType)
            {
                auto pixelValue = itkImage->GetPixel(index);
                rowData[col] = qRgb(pixelValue, pixelValue, pixelValue);
            }
            else
            {
                EERGBITKPixelType pixel = itkImage->GetPixel(index);
                rowData[col] = qRgb(pixel.GetRed(), pixel.GetGreen(), pixel.GetBlue());
            }
        }
    }

    EagleEye::Logger::CENTRAL_LOGGER().LogMessage(
                QString("itkutilities::EEITKImageToQImageAdapter(): isRGBPixelType %1.").arg(isRGBPixelType),
                EagleEye::LOGLEVEL::EE_DEBUG);
    EagleEye::Logger::CENTRAL_LOGGER().LogMessage(
                QString("itkutilities::EEITKImageToQImageAdapter(): Output QImage image width is %1.").arg(qImage.width()),
                EagleEye::LOGLEVEL::EE_DEBUG);
    EagleEye::Logger::CENTRAL_LOGGER().LogMessage(
                QString("itkutilities::EEITKImageToQImageAdapter(): Output QImage image width is %1.").arg(qImage.height()),
                EagleEye::LOGLEVEL::EE_DEBUG);

    if (!isRGBPixelType)
      return qImage.convertToFormat(QImage::Format_Grayscale16);

    return qImage;
}
};
#endif // ITKUTILITIES_H
