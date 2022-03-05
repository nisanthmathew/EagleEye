#include "datahandler.h"
#include "logger.h"
#include "displayformat.h"

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

int DataHandler::GetPreviousSliderValue() const
{
    QMutexLocker locker(m_CommonMutex);
    return m_PreviousSliderValue;
}

void DataHandler::SetPreviousSliderValue(int previousSliderValue)
{
    QMutexLocker locker(m_CommonMutex);
    m_PreviousSliderValue = previousSliderValue;
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
}
