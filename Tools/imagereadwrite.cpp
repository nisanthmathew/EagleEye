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

bool ImageReadWrite::LoadImage()
{
    QString activeFileName = QFileDialog::getOpenFileName(this,
                                                         tr("Open Image"), "C:/", tr("Image Files (*.png *.jpg *.bmp)"));
    EagleEye::DataHandler::DATA_HANDLER().SetActiveFileName(activeFileName);
    QImageReader imageReader(activeFileName);
    QPixmap newPixMap = QPixmap::fromImageReader(&imageReader);
    EagleEye::DataHandler::DATA_HANDLER().SetCurrentImagePixMap(newPixMap);
    return (!newPixMap.isNull());
}

bool ImageReadWrite::SaveImageCopy(const QPixmap &imageToSave)
{
    if (imageToSave.isNull())
    {
        return  false;
    }
    return true;
}
}
