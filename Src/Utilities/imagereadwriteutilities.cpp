#include "imagereadwriteutilities.h"
#include "../Singletons/data.h"
#include "../Singletons/logger.h"

#include <QtWidgets/QFileDialog>
#include <qimagereader.h>

namespace EagleEye
{
ImageReadWrite::ImageReadWrite(QWidget *parent) : QWidget(nullptr)
{

}

bool ImageReadWrite::EELoadImage(QString filePath)
{
    if (filePath.isEmpty())
    {
        filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "C:/", tr("Image Files (*.png *.jpg *.bmp)"));
    }

    EagleEye::Data::SINGLE_INSTANCE().SetActiveFilePath(filePath);
    QImageReader imageReader(filePath);
    QPixmap newPixMap = QPixmap::fromImageReader(&imageReader);
    EagleEye::Data::SINGLE_INSTANCE().SetInputImagePixmap(newPixMap);
    return (!newPixMap.isNull());
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
