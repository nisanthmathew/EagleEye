#include "imageprocessingutilities.h"

namespace EagleEye
{

QPixmap EEEdgeDetection(const QPixmap &image)
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
