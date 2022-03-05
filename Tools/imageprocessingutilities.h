#ifndef IMAGEPROCESSINGUTILITIES_H
#define IMAGEPROCESSINGUTILITIES_H

#include "itkutilities.h"

#include <QPixmap>

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkSobelEdgeDetectionImageFilter.h>

namespace EagleEye
{

QPixmap EEEdgeDetection(const QPixmap &image);

};
#endif // IMAGEPROCESSINGUTILITIES_H
