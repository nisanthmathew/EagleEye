#include "datahandler.h"

#include <QMutexLocker>

#include <iostream>

namespace EagleEye{

DataHandler::DataHandler():
    m_PreviousSliderValue(100)
{

}

QPixmap DataHandler::InputImagePixMap() const
{
    QMutexLocker locker(m_ImageMutex);
    return m_InputImagePixMap;
}

void DataHandler::SetInputImagePixMap(const QPixmap &InputImagePixMap)
{
    QMutexLocker locker(m_ImageMutex);
    std::cout << "InputImagePixMap" << std::endl;
    std::cout << InputImagePixMap.physicalDpiX() << std::endl;
    std::cout << InputImagePixMap.physicalDpiY() << std::endl;
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
