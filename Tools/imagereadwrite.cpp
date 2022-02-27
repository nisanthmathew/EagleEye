#include "imagereadwrite.h"
#include <../datahandler.h>
#include "../logger.h"

#include <QtWidgets/QFileDialog>
#include "qimagereader.h"

namespace EagleEye
{
ImageReadWrite::ImageReadWrite(QWidget *parent) : QWidget(nullptr)
{

}

bool ImageReadWrite::EELoadImage()
{
    QString activeFileName = QFileDialog::getOpenFileName(this,
                                                         tr("Open Image"), "C:/", tr("Image Files (*.png *.jpg *.bmp)"));
    EagleEye::DataHandler::DATA_HANDLER().SetActiveFilePath(activeFileName);
    QImageReader imageReader(activeFileName);
    QPixmap newPixMap = QPixmap::fromImageReader(&imageReader);
    EagleEye::DataHandler::DATA_HANDLER().SetInputImagePixmap(newPixMap);
    return (!newPixMap.isNull());
}

bool ImageReadWrite::EESaveImageCopy(const QPixmap &imageToSave)
{
    if (imageToSave.isNull())
    {
        return  false;
    }

    auto newFileName = QFileDialog::getSaveFileName(this,
                                                    tr("Open Image"), "C:/", tr("Image Files (*.png *.jpg *.bmp)"));

    if (!imageToSave.save(newFileName))
    {
        return false;
    }
    else
    {
        return true;
    }
}
}
