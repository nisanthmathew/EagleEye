#include "logger.h"


namespace EagleEye{

void Logger::LogMessage(const std::string &message, EagleEye::LOGLEVEL loglevel)
{
    std::string loglevelString;
    switch (loglevel) {
    case LOGLEVEL::EE_ERROR:
        loglevelString = "Error";
        break;
    case LOGLEVEL::EE_WARNING:
        loglevelString = "Warning";
        break;
    case LOGLEVEL::EE_INFO:
        loglevelString = "Info";
        break;
    case LOGLEVEL::EE_DEBUG:
        loglevelString = "Debug";
        break;
    default:
        break;
    }
    {
        QMutexLocker locker (m_LogMutex);
        m_LogVector.emplace_back(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString() +
                                                        "; " + message + "; " + loglevelString);
    }
}

void Logger::SetLogtoConsole(const bool logtoConsole)
{
    m_LogToConsole = logtoConsole;
}

}
