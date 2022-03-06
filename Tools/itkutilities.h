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


template <typename T>
typename T::Pointer EEITKImageFromQImage(const QImage &qImage)
{

    typename T::Pointer image = nullptr;
    itk::Image<itk::RGBPixel<float>, 2>::Pointer rgbImage  = nullptr;
    typename T::IndexType start;

    start[0] = 0; // first index on X
    start[1] = 0; // first index on Y

    typename T::SizeType size;
    size[0] = qImage.width(); // size along X
    size[1] = qImage.height(); // size along Y

    typename T::RegionType region;
    region.SetSize(size);
    region.SetIndex(start);

    bool isRGBPixelType = (std::is_same<T,itk::RGBPixel<float>>::value);

    if (!isRGBPixelType)
    {
        image = T::New();
        image->SetRegions(region);
        image->Allocate();
        image->Update();

    }
    else
    {
        rgbImage = itk::Image<itk::RGBPixel<float>, 2>::New();
        rgbImage->SetRegions(region);
        rgbImage->Allocate();
        rgbImage->Update();
    }

    itk::Image<itk::RGBPixel<float>, 2>::PixelType rgbPixel;
    itk::Image<itk::RGBPixel<float>, 2>::IndexType rgbIndex;
    typename T::PixelType tPixel;
    typename itk::Image<T, 2>::IndexType tIndex;

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
                tIndex[0] = col;
                tIndex[1] = row;
                tPixel = (qRed(rowData[col]) + qGreen(rowData[col]) + qBlue(rowData[col])) / 3;
                image->SetPixel(tIndex, tPixel);
            }
        }
    }

    return image;
}


template <typename  T>
QImage EEQImageFromITKImage(const typename itk::Image<T, 2>::Pointer itkImage)
{
    auto width = itkImage->GetLargestPossibleRegion().GetSize()[0];
    auto height = itkImage->GetLargestPossibleRegion().GetSize()[1];

    QImage qImage (QSize(width, height), QImage::Format_RGB32);
    typename itk::Image<T, 2>::IndexType index;

    bool isRGBPixelType = (std::is_same<T,itk::RGBPixel<float>>::value);

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
                itk::Image<itk::RGBPixel<float>, 2>::PixelType pixel = itkImage->GetPixel(index);
                rowData[col] = qRgb(pixel.GetRed(),
                                    pixel.GetGreen(),
                                    pixel.GetBlue());
            }

        }
    }

    if (!isRGBPixelType)
        return qImage.convertToFormat(QImage::Format_Grayscale8);

    return qImage;
}
};
#endif // ITKUTILITIES_H
