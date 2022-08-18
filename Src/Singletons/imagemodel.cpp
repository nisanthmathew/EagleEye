#include "imagemodel.h"

namespace EagleEye{
ImageModel::ImageModel(QObject *parent)
    : QStandardItemModel{parent},
      m_ImageReadWrite(std::unique_ptr<EagleEye::ImageReadWrite>(new EagleEye::ImageReadWrite()))
{
    setColumnCount(1);
    setRowCount(RowCount);

    //initialize data
    SetData(OriginalImagePixmap, QVariant::fromValue(QPixmap()));
    SetData(DisplayedImagePixmap, QVariant::fromValue(QPixmap()));
    SetData(ImageLabelPixmap, QVariant::fromValue(QPixmap()));
    SetData(ROIPixmap, QVariant::fromValue(QPixmap()));
    SetData(RectangularROI, QVariant::fromValue(QRect()));
    SetData(ActiveImagePath, QVariant::fromValue(QString()));
    SetData(ZoomFactor, QVariant::fromValue(1.0f));
    SetData(SelectRectangularROI, QVariant::fromValue(false));
    SetData(ImageViewLabelWidth, QVariant::fromValue(0));
    SetData(ImageViewLabelHeight, QVariant::fromValue(0));

}

QModelIndex ImageModel::index(int row, int column, const QModelIndex &parent) const
{
    return QStandardItemModel::index(row, column, parent);
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
        SetData(ImageModel::OriginalImagePixmap, QVariant::fromValue(newPixmap));
        SetData(ImageModel::ActiveImagePath, QVariant::fromValue(filePath));
        SetData(ImageModel::DisplayedImagePixmap, QVariant::fromValue(newPixmap));
        SetData(ImageModel::ZoomFactor, QVariant::fromValue(1.0f));
        const int width = GetData<int>(ImageModel::ImageViewLabelWidth);
        const int height = GetData<int>(ImageModel::ImageViewLabelHeight);
        newPixmap = newPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        SetData(ImageModel::ImageLabelPixmap, QVariant::fromValue(newPixmap));
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage(QString("ImageModel::SetNewImage(): loading image %1").arg(filePath),
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
    }
    else
    {
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("ImageModel::SetNewImage(): Failed to load image",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
    }
}

void ImageModel::SaveDisplayedImage()
{
    m_ImageReadWrite->EESaveImageCopy(GetData<QPixmap>(ImageModel::DisplayedImagePixmap));
}

void ImageModel::SetZoomFactor(QWheelEvent *e)
{
    int zoomDir = e->angleDelta().y() / std::abs(e->angleDelta().y());
    const float currentZoomFactor = GetData<float>(ImageModel::ZoomFactor) + (zoomDir * 0.1);
    if (currentZoomFactor >= 8.0 || currentZoomFactor <= 0.5) //zoom out is permitted only till half size and zoom in for 8 times the size
        return;

    SetData(ImageModel::ZoomFactor, QVariant::fromValue(currentZoomFactor));

    QPixmap displayedPixmap = GetData<QPixmap>(ImageModel::DisplayedImagePixmap);
    const int width = GetData<int>(ImageModel::ImageViewLabelWidth);
    const int height = GetData<int>(ImageModel::ImageViewLabelHeight);
    displayedPixmap = displayedPixmap.scaled(width * currentZoomFactor, height * currentZoomFactor, Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation);
    SetData(ImageModel::ImageLabelPixmap, QVariant::fromValue(displayedPixmap));
    ClearRectangularROI();
}

void ImageModel::ResizeImageLabel(const QSize &size)
{
    const int width = size.width();
    const int height = size.height();
    SetData(ImageModel::ImageViewLabelWidth, QVariant::fromValue(width));
    SetData(ImageModel::ImageViewLabelHeight, QVariant::fromValue(height));
    QPixmap displayedPixmap = GetData<QPixmap>(ImageModel::DisplayedImagePixmap);
    const float zoomFactor = GetData<float>(ImageModel::ZoomFactor);
    displayedPixmap = displayedPixmap.scaled(width * zoomFactor, height * zoomFactor, Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation);
    ClearRectangularROI();
    SetData(ImageModel::ImageLabelPixmap, QVariant::fromValue(displayedPixmap));
}

void ImageModel::ConvertDisplayFormat(const DisplayFormats displayFormat)
{
    auto pixmapToBeProcessed = GetData<QPixmap>(EagleEye::ImageModel::DisplayedImagePixmap);
    if (GetData<bool>(EagleEye::ImageModel::SelectRectangularROI)) // use ROI option select the use the ROI image
    {
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("EEImageProcessingMenu::ConvertDisplayFormat(): ROI is valid, hence using it.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        pixmapToBeProcessed = GetData<QPixmap>(EagleEye::ImageModel::ROIPixmap);
    }
    QPixmap imageToBeDisplayed;

    switch (displayFormat)
    {
    case EagleEye::DisplayFormats::GreyScale:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("EEImageProcessingMenu::ConvertDisplayFormat(): Converting to Greyscale.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        if (GetData<bool>(EagleEye::ImageModel::SelectRectangularROI))
        {
            const int startX = GetData<QRect>(EagleEye::ImageModel::RectangularROI).topLeft().x();
            const int startY = GetData<QRect>(EagleEye::ImageModel::RectangularROI).topLeft().y();
            imageToBeDisplayed = CombineROIAndDisplayedPixmap(
                        ConvertRGBToGreyScale(pixmapToBeProcessed),
                        GetData<QPixmap>(EagleEye::ImageModel::ImageLabelPixmap), startX, startY);
        }
        else //if no ROI select simply process the entire image
        {
            imageToBeDisplayed = ConvertRGBToGreyScale(pixmapToBeProcessed);
        }
        break;
    case EagleEye::DisplayFormats::Edge:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::ConvertDisplayFormat(): Converting to Edge.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        if (GetData<bool>(EagleEye::ImageModel::SelectRectangularROI))
        {
            const int startX = GetData<QRect>(EagleEye::ImageModel::RectangularROI).topLeft().x();
            const int startY = GetData<QRect>(EagleEye::ImageModel::RectangularROI).topLeft().y();
            imageToBeDisplayed = EagleEye::CombineROIAndDisplayedPixmap(
                        EagleEye::ConvertRGBToEdges(pixmapToBeProcessed),
                        GetData<QPixmap>(EagleEye::ImageModel::ImageLabelPixmap), startX, startY);
        }
        else //if no ROI select simply process the entire image
        {
            imageToBeDisplayed = EagleEye::ConvertRGBToEdges(pixmapToBeProcessed);
        }
        break;
    case EagleEye::DisplayFormats::Original:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("EEImageProcessingMenu::ConvertDisplayFormat(): Reverting to Greyscale.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        imageToBeDisplayed = GetData<QPixmap>(EagleEye::ImageModel::OriginalImagePixmap);
        break;
    }

    const float zoomFactor = GetData<float>(ImageModel::ZoomFactor);
    SetData(EagleEye::ImageModel::DisplayedImagePixmap, QVariant::fromValue(imageToBeDisplayed));
    SetData(EagleEye::ImageModel::ImageLabelPixmap, QVariant::fromValue(
                imageToBeDisplayed.scaled(GetData<int>(ImageModel::ImageViewLabelWidth) * zoomFactor,
                                          GetData<int>(ImageModel::ImageViewLabelHeight) * zoomFactor,
                                          Qt::KeepAspectRatio, Qt::SmoothTransformation)));
}

void ImageModel::SelectRectangularRegionOfInterest(bool start)
{
    SetData(EagleEye::ImageModel::SelectRectangularROI, QVariant::fromValue(start));
    ClearRectangularROI();
}

void ImageModel::SetRectangularROI(const QRect &ROI)
{
    SetData(EagleEye::ImageModel::RectangularROI, QVariant::fromValue(ROI));
    SetData(EagleEye::ImageModel::ROIPixmap, QVariant::fromValue(GetData<QPixmap>(EagleEye::ImageModel::ImageLabelPixmap).copy(ROI)));
}

void ImageModel::ClearRectangularROI()
{
    SetData(EagleEye::ImageModel::ROIPixmap, QVariant::fromValue(QPixmap()));
    SetData(EagleEye::ImageModel::RectangularROI, QVariant::fromValue(QRect()));
}

}
