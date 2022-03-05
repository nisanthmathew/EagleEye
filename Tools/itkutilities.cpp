#include "itkutilities.h"

namespace EagleEye
{

EERGBImageType::Pointer ITKImageFromPixmap(const QPixmap &qPixmap)
{
    QImage qImage = qPixmap.toImage();

    EERGBImageType::Pointer image = EERGBImageType::New();
    EERGBImageType::IndexType start;

    start[0] = 0; // first index on X
    start[1] = 0; // first index on Y

    EERGBImageType::SizeType size;
    size[0] = qImage.width(); // size along X
    size[1] = qImage.height(); // size along Y

    EERGBImageType::RegionType region;
    region.SetSize(size);
    region.SetIndex(start);

    image->SetRegions(region);
    image->Allocate();
    image->Update();

    EERGBImageType::IndexType index;
    EERGBImageType::PixelType pixel;

    for (int row = 0; row < qImage.height(); row++)
    {
        QRgb *rowData = (QRgb*)qImage.scanLine(row);
        for (int col = 0; col < qImage.width(); col++)
        {
            pixel.Set(qRed(rowData[col]), qGreen(rowData[col]), qBlue(rowData[col]));
            index[0] = col;
            index[1] = row;
            image->SetPixel(index, pixel);
        }
    }

    return image;
}

QImage QImageFromITKImage(const EERGBImageType::Pointer itkImage)
{
    auto width = itkImage->GetLargestPossibleRegion().GetSize()[0];
    auto height = itkImage->GetLargestPossibleRegion().GetSize()[1];

    QImage qImage (QSize(width, height), QImage::Format_RGB32);
    EERGBImageType::IndexType index;
    EERGBImageType::PixelType pixel;

    for (int row = 0; row < height; row++)
    {
        QRgb *rowData = (QRgb*)qImage.scanLine(row);
        for (int col = 0; col < width; col++)
        {
            index[0] = col;
            index[1] = row;
            auto pixelValueR = itkImage->GetPixel(index)[0];
            auto pixelValueG = itkImage->GetPixel(index)[1];
            auto pixelValueB = itkImage->GetPixel(index)[2];
            rowData[col] = qRgb(pixelValueR, pixelValueG, pixelValueB);
        }
    }
    return qImage;
}
}
