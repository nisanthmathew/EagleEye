#include "imagemodel.h"

#include <../Singletons/logger.h>
#include <../Singletons/imageviewcontroller.h>

#include <../Utilities/displayformatutilities.h>

namespace EagleEye{
ImageModel::ImageModel(QObject *parent)
    : QStandardItemModel{parent},
      m_ImageReadWrite(std::unique_ptr<EagleEye::ImageReadWrite>(new EagleEye::ImageReadWrite()))
{
    setColumnCount(1);
    setRowCount(static_cast<int>(ImageModelIndex::RowCount));

    //initialize data
    SetData(ImageModelIndex::OriginalImagePixmap, QVariant::fromValue(QPixmap()));
    SetData(ImageModelIndex::DisplayedImagePixmap, QVariant::fromValue(QPixmap()));
    SetData(ImageModelIndex::ImageLabelPixmap, QVariant::fromValue(QPixmap()));
    SetData(ImageModelIndex::ROIPixmap, QVariant::fromValue(QPixmap()));
    SetData(ImageModelIndex::RectangularROI, QVariant::fromValue(QRect()));
    SetData(ImageModelIndex::ActiveImagePath, QVariant::fromValue(QString()));
    SetData(ImageModelIndex::ZoomFactor, QVariant::fromValue(1.0f));
    SetData(ImageModelIndex::SelectRectangularROI, QVariant::fromValue(false));
    SetData(ImageModelIndex::ImageViewLabelWidth, QVariant::fromValue(0));
    SetData(ImageModelIndex::ImageViewLabelHeight, QVariant::fromValue(0));

}

QModelIndex ImageModel::GetIndex(const ImageModelIndex row, int column, const QModelIndex &parent) const
{
    return QStandardItemModel::index(static_cast<int>(row), column, parent);
}

void ImageModel::TriggerDataChange(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    emit dataChanged(topLeft, bottomRight);
}

void ImageModel::SetNewImage()
{
    QString filePath;
    auto newPixmap {m_ImageReadWrite->EELoadImage(filePath)};
    if (!newPixmap.isNull())
    {
        SetData(ImageModelIndex::OriginalImagePixmap, QVariant::fromValue(newPixmap));
        SetData(ImageModelIndex::ActiveImagePath, QVariant::fromValue(filePath));
        SetData(ImageModelIndex::DisplayedImagePixmap, QVariant::fromValue(newPixmap));
        SetData(ImageModelIndex::ZoomFactor, QVariant::fromValue(1.0f));
        const int width = GetData<int>(ImageModelIndex::ImageViewLabelWidth);
        const int height = GetData<int>(ImageModelIndex::ImageViewLabelHeight);
        newPixmap = newPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        SetData(ImageModelIndex::ImageLabelPixmap, QVariant::fromValue(newPixmap));
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage(QString("ImageModel::SetNewImage(): loading image %1").arg(filePath),
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        ClearRectangularROI();
    }
    else
    {
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("ImageModel::SetNewImage(): Failed to load image",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
    }
}

void ImageModel::SaveDisplayedImage()
{
    m_ImageReadWrite->EESaveImageCopy(GetData<QPixmap>(ImageModelIndex::DisplayedImagePixmap));
}

void ImageModel::SetZoomFactor(QWheelEvent *e)
{
    int zoomDir = e->angleDelta().y() / std::abs(e->angleDelta().y());
    const float currentZoomFactor = GetData<float>(ImageModelIndex::ZoomFactor) + (zoomDir * 0.1);
    if (currentZoomFactor >= 8.0 || currentZoomFactor <= 0.5) //zoom out is permitted only till half size and zoom in for 8 times the size
        return;

    SetData(ImageModelIndex::ZoomFactor, QVariant::fromValue(currentZoomFactor));

    QPixmap displayedPixmap = GetData<QPixmap>(ImageModelIndex::DisplayedImagePixmap);
    const int width = GetData<int>(ImageModelIndex::ImageViewLabelWidth);
    const int height = GetData<int>(ImageModelIndex::ImageViewLabelHeight);
    displayedPixmap = displayedPixmap.scaled(width * currentZoomFactor, height * currentZoomFactor, Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation);
    SetData(ImageModelIndex::ImageLabelPixmap, QVariant::fromValue(displayedPixmap));
    ClearRectangularROI();
}

void ImageModel::ResizeImageLabel(const QSize &size)
{
    const int width = size.width();
    const int height = size.height();
    SetData(ImageModelIndex::ImageViewLabelWidth, QVariant::fromValue(width));
    SetData(ImageModelIndex::ImageViewLabelHeight, QVariant::fromValue(height));
    QPixmap displayedPixmap = GetData<QPixmap>(ImageModelIndex::DisplayedImagePixmap);
    const float zoomFactor = GetData<float>(ImageModelIndex::ZoomFactor);
    displayedPixmap = displayedPixmap.scaled(width * zoomFactor, height * zoomFactor, Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation);
    ClearRectangularROI();
    SetData(ImageModelIndex::ImageLabelPixmap, QVariant::fromValue(displayedPixmap));
}

void ImageModel::ConvertDisplayFormat(const DisplayFormats displayFormat)
{
    auto pixmapToBeProcessed = GetData<QPixmap>(ImageModelIndex::DisplayedImagePixmap);
    if (GetData<bool>(ImageModelIndex::SelectRectangularROI)) // use ROI option select the use the ROI image
    {
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("EEImageProcessingMenu::ConvertDisplayFormat(): ROI is valid, hence using it.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        pixmapToBeProcessed = GetData<QPixmap>(ImageModelIndex::ROIPixmap);
    }
    QPixmap imageToBeDisplayed;

    switch (displayFormat)
    {
    case EagleEye::DisplayFormats::GreyScale:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("EEImageProcessingMenu::ConvertDisplayFormat(): Converting to Greyscale.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        if (GetData<bool>(ImageModelIndex::SelectRectangularROI))
        {
            const int startX = GetData<QRect>(ImageModelIndex::RectangularROI).topLeft().x();
            const int startY = GetData<QRect>(ImageModelIndex::RectangularROI).topLeft().y();
            imageToBeDisplayed = CombineROIAndDisplayedPixmap(
                        ConvertRGBToGreyScale(pixmapToBeProcessed),
                        GetData<QPixmap>(ImageModelIndex::ImageLabelPixmap), startX, startY);
        }
        else //if no ROI select simply process the entire image
        {
            imageToBeDisplayed = ConvertRGBToGreyScale(pixmapToBeProcessed);
        }
        break;
    case EagleEye::DisplayFormats::Edge:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::ConvertDisplayFormat(): Converting to Edge.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        if (GetData<bool>(ImageModelIndex::SelectRectangularROI))
        {
            const int startX = GetData<QRect>(ImageModelIndex::RectangularROI).topLeft().x();
            const int startY = GetData<QRect>(ImageModelIndex::RectangularROI).topLeft().y();
            imageToBeDisplayed = EagleEye::CombineROIAndDisplayedPixmap(
                        EagleEye::ConvertRGBToEdges(pixmapToBeProcessed),
                        GetData<QPixmap>(ImageModelIndex::ImageLabelPixmap), startX, startY);
        }
        else //if no ROI select simply process the entire image
        {
            imageToBeDisplayed = EagleEye::ConvertRGBToEdges(pixmapToBeProcessed);
        }
        break;
    case EagleEye::DisplayFormats::Original:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("EEImageProcessingMenu::ConvertDisplayFormat(): Reverting to Greyscale.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        imageToBeDisplayed = GetData<QPixmap>(ImageModelIndex::OriginalImagePixmap);
        break;
    }

    const float zoomFactor = GetData<float>(ImageModelIndex::ZoomFactor);
    SetData(ImageModelIndex::DisplayedImagePixmap, QVariant::fromValue(imageToBeDisplayed));
    SetData(ImageModelIndex::ImageLabelPixmap, QVariant::fromValue(
                imageToBeDisplayed.scaled(GetData<int>(ImageModelIndex::ImageViewLabelWidth) * zoomFactor,
                                          GetData<int>(ImageModelIndex::ImageViewLabelHeight) * zoomFactor,
                                          Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    ClearRectangularROI();
}

void ImageModel::SelectRectangularRegionOfInterest(bool start)
{
    SetData(ImageModelIndex::SelectRectangularROI, QVariant::fromValue(start));
    ClearRectangularROI();
}

void ImageModel::SetRectangularROI(const QRect &ROI)
{
    SetData(ImageModelIndex::RectangularROI, QVariant::fromValue(ROI));
    SetData(ImageModelIndex::ROIPixmap, QVariant::fromValue(GetData<QPixmap>(ImageModelIndex::ImageLabelPixmap).copy(ROI)));
}

void ImageModel::ClearRectangularROI()
{
    SetData(ImageModelIndex::ROIPixmap, QVariant::fromValue(QPixmap()));
    SetData(ImageModelIndex::RectangularROI, QVariant::fromValue(QRect()));
}

}
