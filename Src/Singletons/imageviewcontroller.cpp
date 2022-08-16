#include "imageviewcontroller.h"

#include <QEvent>
#include <QLabel>
#include <QWheelEvent>
namespace EagleEye {

ImageViewController::ImageViewController(QObject *parent, EagleEye::ImageModel *model)
    : QObject{parent},
      m_ImageModel(model)
{

}

bool ImageViewController::eventFilter(QObject *object, QEvent *e)
{
    switch (e->type())
    {
    case QEvent::Wheel:
    {
        QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent *>(e);
        m_ImageModel->SetZoomFactor(wheelEvent);
        break;
    }
    case QEvent::Resize:
    {
        m_ImageModel->ResizeImageLabel(this->parent()->findChild<QLabel *>("imageLabel")->size());
    }
    default:
        break;
    }
    return false;
}

EagleEye::ImageModel *ImageViewController::GetImageModel() const
{
    return m_ImageModel;
}

void ImageViewController::ConvertImageDisplayFormat(DisplayFormats displayFormat)
{
    m_ImageModel->ConvertDisplayFormat(displayFormat);
}

void ImageViewController::OpenImage()
{
    m_ImageModel->SetNewImage();
}

void ImageViewController::SaveImageCopy()
{
    m_ImageModel->SaveDisplayedImage();
}
}
