#include "logger.h"

#include <sstream>
namespace EagleEye{

void EagleEye::Logger::LogMessage(QString &message, EagleEye::LOGLEVEL loglevel)
{    
    std::string loglevelString;
    switch (loglevel) {
    case ERROR:
        loglevelString = "Error";
        break;
    case WARNING:
        loglevelString = "Warning";
        break;
    case INFO:
        loglevelString = "Info";
        break;
    case DEBUG:
        loglevelString = "Debug";
        break;
    default:
        break;
    }
    std::stringstream ss;
    ss << message.toStdString() << "; " << loglevelString << "; " << QDateTime::currentDateTime().toString().toStdString();
    {
        QMutexLocker locker (m_LogMutex);
        m_LogVector.push_back(ss.str());
    }
}
}
