#include "../Utilities/displayformatutilities.h"

#include "imageprocessingutilities.h"

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

QPixmap CombineROIAndDisplayedPixmap(const QPixmap &roiPixmap, const QPixmap &displayedPixmap, int startX, int startY)
{
    QImage roiImage = roiPixmap.toImage();
    QImage displayedImage = displayedPixmap.toImage();

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
