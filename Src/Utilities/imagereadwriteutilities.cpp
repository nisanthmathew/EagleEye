#include "imagereadwriteutilities.h"
#include "itkutilities.h"
#include "../Singletons/data.h"
#include "../Singletons/logger.h"

#include <QtWidgets/QFileDialog>
#include <qimagereader.h>

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkImageFileWriter.h"
#include "itkNumericTraits.h"

namespace EagleEye
{
ImageReadWrite::ImageReadWrite(QWidget *parent) : QWidget(nullptr)
{

}

QPixmap EagleEye::ImageReadWrite::EELoadDicomImage(const QString &filePath)
{
    using ReaderType = itk::ImageFileReader<EEImageType>;
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(filePath.toStdString());

    using RescaleType = itk::RescaleIntensityImageFilter<EEImageType, EEImageType>;
    RescaleType::Pointer rescale = RescaleType::New();
    rescale->SetInput(reader->GetOutput());
    rescale->SetOutputMinimum(0);
    rescale->SetOutputMaximum(255);
    rescale->Update();

    const auto dicomImage = EEITKImageToQImageAdapter<EEPixelType>(rescale->GetOutput());
    return QPixmap::fromImage(dicomImage);
}

QPixmap ImageReadWrite::EELoadImage(QString &filePath)
{
    if (filePath.isEmpty())
    {
        filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "C:/", tr("Image Files (*.png *.jpg *.bmp *.dcm)"));
    }

    QPixmap newPixMap;

    if (filePath.contains(".dcm", Qt::CaseInsensitive))
    {
        newPixMap = EELoadDicomImage(filePath);
    }
    else
    {
        QImageReader imageReader(filePath);
        newPixMap = QPixmap::fromImageReader(&imageReader);
    }

    return newPixMap;
}

bool ImageReadWrite::EESaveImageCopy(const QPixmap &imageToSave, QString filePath)
{
    if (imageToSave.isNull())
    {
        return  false;
    }

    if (filePath.isEmpty())
    {
        filePath = QFileDialog::getSaveFileName(this, tr("Open Image"), "C:/", tr("Image Files (*.png *.jpg *.bmp)"));
    }

    if (!imageToSave.save(filePath))
    {
        return false;
    }
    else
    {
        return true;
    }
}
}
