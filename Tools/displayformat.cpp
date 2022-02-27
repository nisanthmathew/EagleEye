#include "displayformat.h"
#include <../datahandler.h>
#include "../logger.h"
#include "itkutilities.h"

namespace EagleEye
{
QPixmap ConvertRGBToGreyScale(const QPixmap &image)
{
    QImage greyScaleImage = image.toImage().convertToFormat(QImage::Format_Grayscale8);
    QPixmap greyScalePixmap = QPixmap::fromImage(greyScaleImage);
    return greyScalePixmap;
}

QPixmap ConvertRGBToEdges(const QPixmap &image)
{
    return EdgeDetection(image);
}

QPixmap EdgeDetection(const QPixmap &image)
{
    auto itkimage = ITKImageFromPixmap(image);

    using FilterType = itk::SobelEdgeDetectionImageFilter<EEImageType, EEImageType>;
    FilterType::Pointer filter = FilterType::New();
    filter->SetInput(itkimage);
    filter->Update();
    auto itkImage = filter->GetOutput();
    return PixmapFromITKImage(itkImage);
}
}
