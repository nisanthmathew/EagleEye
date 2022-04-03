#include "datahandler.h"
#include "logger.h"
#include "displayformatutilities.h"

#include <QMutexLocker>

#include <iostream>

namespace EagleEye{

QPixmap DataHandler::GetOriginalImagePixmap() const
{
    QMutexLocker locker(m_ImageMutex);
    return m_InputImagePixMap;
}

void DataHandler::SetInputImagePixmap(const QPixmap &inputImagePixMap)
{
    QMutexLocker locker(m_ImageMutex);
    m_InputImagePixMap = inputImagePixMap;
}

QString DataHandler::GetActiveFilePath() const
{
    QMutexLocker locker(m_CommonMutex);
    return m_ActiveFilePath;
}

void DataHandler::SetActiveFilePath(const QString &ActiveFilePath)
{
    QMutexLocker locker(m_CommonMutex);
    m_ActiveFilePath = ActiveFilePath;
}

const QPixmap &DataHandler::GetDisplayedImagePixmap() const
{
    QMutexLocker locker(m_ImageMutex);
    return m_DisplayedImagePixmap;
}

void DataHandler::SetDisplayedImagePixmap(const QPixmap &newDisplayedImagePixmap)
{
    QMutexLocker locker(m_ImageMutex);
    m_DisplayedImagePixmap = newDisplayedImagePixmap;
}

const bool DataHandler::GetSelectROI() const
{
    return m_SelectROI;
}

void DataHandler::SetSelectROI(const bool selectROI)
{
    m_SelectROI = selectROI;
}

float DataHandler::GetZoomFactor() const
{
    return m_ZoomFactor;
}

void DataHandler::SetZoomFactor(float newZoomFactor)
{
    m_ZoomFactor = newZoomFactor;
}

const QRect &DataHandler::GetRegionOfinterset() const
{
    return m_RegionOfinterset;
}

void DataHandler::SetRegionOfinterset(const QRect &newRegionOfinterset)
{
    m_RegionOfinterset = newRegionOfinterset;
}

const QPixmap &DataHandler::GetROIPixmap() const
{
    return m_ROIPixmap;
}

void DataHandler::SetROIPixmap(const QPixmap &newROIPixmap)
{
    m_ROIPixmap = newROIPixmap;
}

const QPixmap &DataHandler::GetImageLabelPixmap() const
{
    return m_ImageLabelPixmap;
}

void DataHandler::SetImageLabelPixmap(const QPixmap &newImageLabelPixmap)
{
    m_ImageLabelPixmap = newImageLabelPixmap;
}

const QPixmap &DataHandler::GetImageToBeDisplayed() const
{
    return m_ImageToBeDisplayed;
}

void DataHandler::SetImageToBeDisplayed(const QPixmap &newImageToBeDisplayed)
{
    m_ImageToBeDisplayed = newImageToBeDisplayed;
}

}
