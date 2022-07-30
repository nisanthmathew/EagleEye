#include "../Singletons/data.h"
#include "../Singletons/logger.h"
#include "../Utilities/displayformatutilities.h"

#include <QMutexLocker>
#include <QApplication>
#include <QDesktopWidget>

#include <iostream>

namespace EagleEye{

QPixmap Data::GetOriginalImagePixmap() const
{
    QMutexLocker locker(m_ImageMutex);
    return m_InputImagePixMap;
}

void Data::SetInputImagePixmap(const QPixmap &inputImagePixMap)
{
    QMutexLocker locker(m_ImageMutex);
    m_InputImagePixMap = inputImagePixMap;
}

QString Data::GetActiveFilePath() const
{
    QMutexLocker locker(m_CommonMutex);
    return m_ActiveFilePath;
}

void Data::SetActiveFilePath(const QString &ActiveFilePath)
{
    QMutexLocker locker(m_CommonMutex);
    m_ActiveFilePath = ActiveFilePath;
}

const QPixmap &Data::GetDisplayedImagePixmap() const
{
    QMutexLocker locker(m_ImageMutex);
    return m_DisplayedImagePixmap;
}

void Data::SetDisplayedImagePixmap(const QPixmap &newDisplayedImagePixmap)
{
    QMutexLocker locker(m_ImageMutex);
    m_DisplayedImagePixmap = newDisplayedImagePixmap;
}

const bool Data::GetSelectROI() const
{
    return m_SelectROI;
}

void Data::SetSelectROI(const bool selectROI)
{
    m_SelectROI = selectROI;
}

float Data::GetZoomFactor() const
{
    return m_ZoomFactor;
}

void Data::SetZoomFactor(float newZoomFactor)
{
    m_ZoomFactor = newZoomFactor;
}

const QRect &Data::GetRegionOfinterset() const
{
    return m_RegionOfinterset;
}

void Data::SetRegionOfinterset(const QRect &newRegionOfinterset)
{
    m_RegionOfinterset = newRegionOfinterset;
}

const QPixmap &Data::GetROIPixmap() const
{
    return m_ROIPixmap;
}

void Data::SetROIPixmap(const QPixmap &newROIPixmap)
{
    m_ROIPixmap = newROIPixmap;
}

const QPixmap &Data::GetImageLabelPixmap() const
{
    return m_ImageLabelPixmap;
}

void Data::SetImageLabelPixmap(const QPixmap &newImageLabelPixmap)
{
    m_ImageLabelPixmap = newImageLabelPixmap;
}

const QPixmap &Data::GetImageToBeDisplayed() const
{
    return m_ImageToBeDisplayed;
}

void Data::SetImageToBeDisplayed(const QPixmap &newImageToBeDisplayed)
{
    m_ImageToBeDisplayed = newImageToBeDisplayed;
}

float Data::GetDisplayPixelLengthInMillimeter()
{
    const int width_mm  = QApplication::desktop()->widthMM();
    const int height_mm = QApplication::desktop()->heightMM();
    const int numeberOfXPixels  = QApplication::desktop()->width();
    const int numeberOfYPixels = QApplication::desktop()->height();

    const float pixelXSizeInMillimeter = static_cast<float>(width_mm) / numeberOfXPixels;
    const float pixelYSizeInMillimeter = static_cast<float>(height_mm) / numeberOfYPixels;
    const float pixelSizeInMillimeter = (pixelXSizeInMillimeter + pixelYSizeInMillimeter) / 2.0f;

    EagleEye::Logger::CENTRAL_LOGGER().LogMessage(
                QString("Data::GetDisplayPixelLengthInMillimeter(): pixelSizeInMillimeter is %1. "
                        "Screen width_mm is %2, Screen height_mm is %3 "
                        "numeberOfXPixels is %4, numeberOfYPixels is %5")
                .arg(QString::number(pixelSizeInMillimeter)).arg(width_mm).arg(height_mm).arg(numeberOfXPixels).arg(numeberOfYPixels),
                EagleEye::LOGLEVEL::EE_DEBUG);

    return pixelSizeInMillimeter;
}


}
