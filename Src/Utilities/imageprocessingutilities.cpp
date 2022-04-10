#include "imageprocessingutilities.h"

namespace EagleEye
{

QPixmap EEEdgeDetection(const QPixmap &image)
{

    auto itkGreyImage = EEQImageToITKImageAdapter<EEImageType>(image.toImage());

    using SobelFilterType = itk::SobelEdgeDetectionImageFilter<EEImageType, EEImageType>;
    SobelFilterType::Pointer sobelFilter = SobelFilterType::New();
    sobelFilter->SetInput(itkGreyImage);
    sobelFilter->Update();

    auto edgeImage = EEITKImageToQImageAdapter<EEPixelType>(sobelFilter->GetOutput());
    edgeImage.invertPixels(QImage::InvertRgb);
    return QPixmap::fromImage(edgeImage);
}

}