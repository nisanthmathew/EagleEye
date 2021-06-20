#include "datahandler.h"
#include "logger.h"

#include <QMutexLocker>

#include <iostream>

namespace EagleEye{

QPixmap DataHandler::InputImagePixMap() const
{
    QMutexLocker locker(m_ImageMutex);
    return m_InputImagePixMap;
}

void DataHandler::SetInputImagePixMap(const QPixmap &InputImagePixMap)
{
    QMutexLocker locker(m_ImageMutex);
    QString message {QString("InputImagePixMap DpiX: %1, DpiY: %2").arg(InputImagePixMap.physicalDpiX()).
                    arg(InputImagePixMap.physicalDpiY())};
    Logger::CENTRAL_LOGGER().LogMessage(message,EagleEye::LOGLEVEL::DEBUG);
    m_InputImagePixMap = InputImagePixMap;
}

int DataHandler::PreviousSliderValue() const
{
    QMutexLocker locker(m_CommonMutex);
    return m_PreviousSliderValue;
}

void DataHandler::SetPreviousSliderValue(int previousSliderValue)
{
    QMutexLocker locker(m_CommonMutex);
    m_PreviousSliderValue = previousSliderValue;
}

QString DataHandler::ActiveFileName() const
{
    QMutexLocker locker(m_CommonMutex);
    return m_ActiveFileName;
}

void DataHandler::SetActiveFileName(const QString &ActiveFileName)
{
    QMutexLocker locker(m_CommonMutex);
    m_ActiveFileName = ActiveFileName;
}
}
