#include "imageprocessingutilities.h"

#include "itkutilities.h"

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkSobelEdgeDetectionImageFilter.h>

#include <QPixmap>

namespace EagleEye
{

QPixmap EEEdgeDetection(const QPixmap &image)
{

    const auto itkGreyImage = EEQImageToITKImageAdapter<EEFloatITKImageType>(image.toImage());

    using SobelFilterType = itk::SobelEdgeDetectionImageFilter<EEFloatITKImageType, EEFloatITKImageType>;
    SobelFilterType::Pointer sobelFilter = SobelFilterType::New();
    sobelFilter->SetInput(itkGreyImage);
    sobelFilter->Update();

    auto edgeImage = EEITKImageToQImageAdapter<EEFloatPixelType>(sobelFilter->GetOutput());
    edgeImage.invertPixels(QImage::InvertRgb);
    return QPixmap::fromImage(edgeImage);
}

}
