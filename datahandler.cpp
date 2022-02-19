#include "datahandler.h"
#include "logger.h"
#include "displayformat.h"

#include <QMutexLocker>

#include <iostream>

namespace EagleEye{

QPixmap DataHandler::GetCurrentImagePixMap() const
{
    QMutexLocker locker(m_ImageMutex);
    return m_InputImagePixMap;
}

void DataHandler::SetCurrentImagePixMap(const QPixmap &CurrentImagePixMap)
{
    QMutexLocker locker(m_ImageMutex);
    m_InputImagePixMap = CurrentImagePixMap;
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
}
