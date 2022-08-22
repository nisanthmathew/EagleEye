#include "logger.h"

#include <sstream>
namespace EagleEye{

void EagleEye::Logger::LogMessage(QString message, EagleEye::LOGLEVEL loglevel)
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
    std::stringstream ss;
    ss << QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString() <<
          "; " << message.toStdString() << "; " << loglevelString;
    {
        QMutexLocker locker (m_LogMutex);
        m_LogVector.push_back(ss.str());
    }
    std::cout << ss.str() << std::endl;
}
}
