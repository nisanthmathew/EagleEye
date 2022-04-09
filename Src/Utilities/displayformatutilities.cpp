#include "../Utilities/displayformatutilities.h"
#include <../datahandler.h>


namespace EagleEye
{
QPixmap ConvertRGBToGreyScale(const QPixmap &image)
{
    QImage greyScaleImage = image.toImage().convertToFormat(QImage::Format_Grayscale8);
    return QPixmap::fromImage(greyScaleImage);
}

QPixmap ConvertRGBToEdges(const QPixmap &image)
{
    return EEEdgeDetection(image);
}

QPixmap CombineROIAndDisplayedPixmap(const QPixmap &roiPixmap, const QPixmap &displayedPixmap)
{
    if (!EagleEye::DataHandler::SINGLE_INSTANCE().GetSelectROI())//if no ROI select simply return the roi pixmap
    {
        return roiPixmap;
    }

    QImage roiImage = roiPixmap.toImage();
    QImage displayedImage = displayedPixmap.toImage();
    int startX = EagleEye::DataHandler::SINGLE_INSTANCE().GetRegionOfinterset().topLeft().x();
    int startY = EagleEye::DataHandler::SINGLE_INSTANCE().GetRegionOfinterset().topLeft().y();

    for (int row = 0; row < roiImage.height(); row++)
    {
        QRgb *rowDataROI = (QRgb*)roiImage.scanLine(row);
        QRgb *rowDataDisplayedImage = (QRgb*)displayedImage.scanLine(startY);
        int colDisplayedImage = startX;
        for (int col = 0; col < roiImage.width(); col++)
        {
            rowDataDisplayedImage[colDisplayedImage] = rowDataROI[col];
            colDisplayedImage++;
        }
        startY++;
    }
    return QPixmap::fromImage(displayedImage);
}

}
