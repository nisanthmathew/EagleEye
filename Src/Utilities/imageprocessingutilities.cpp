#include "imageprocessingutilities.h"

#include "itkutilities.h"

namespace EagleEye
{

QPixmap EEEdgeDetection(const QPixmap &image)
{

    auto itkGreyImage = EEQImageToITKImageAdapter<EEFloatITKImageType>(image.toImage());

    using SobelFilterType = itk::SobelEdgeDetectionImageFilter<EEFloatITKImageType, EEFloatITKImageType>;
    SobelFilterType::Pointer sobelFilter = SobelFilterType::New();
    sobelFilter->SetInput(itkGreyImage);
    sobelFilter->Update();

    auto edgeImage = EEITKImageToQImageAdapter<EEFloatPixelType>(sobelFilter->GetOutput());
    edgeImage.invertPixels(QImage::InvertRgb);
    return QPixmap::fromImage(edgeImage);
}

}
