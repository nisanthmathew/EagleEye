#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QDate>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>

#include <iostream>
#include <fstream>
#include <sstream>

namespace  EagleEye {
enum class LOGLEVEL
{
    EE_ERROR,
    EE_WARNING,
    EE_INFO,
    EE_DEBUG
};

class Logger : public QObject
{
    Q_OBJECT
private:
    Logger():
        m_LogToConsole(false)
    {
        QString filename {QDate::currentDate().toString(Qt::ISODate) + ".txt"};
        QFile logFile{filename};
        QTimer *timer = new QTimer(this);
        QObject::connect(timer, &QTimer::timeout, this, [this, filename](){

            QMutexLocker locker (m_LogMutex);
            if (m_LogVector.empty())
                return;

            std::ofstream logFileStream;
            logFileStream.open(filename.toStdString(), std::fstream::app);
            for (const auto &message : m_LogVector)
            {
                logFileStream << message << std::endl;
                if (m_LogToConsole)
                {
                    std::cout << message << std::endl;
                }
            }
            m_LogVector.clear();
            logFileStream.close();
        });
        timer->start(100);
    }
    std::vector<std::string> m_LogVector;
    QMutex *m_LogMutex;
    bool m_LogToConsole;
public:
    static Logger& CENTRAL_LOGGER(){
        static Logger theInstance;
        return theInstance;
    }
    Logger (const Logger &) = delete;
    Logger& operator=(const Logger &) = delete;

    void LogMessage(const std::string &message, EagleEye::LOGLEVEL loglevel);
    void SetLogtoConsole(const bool logtoConsole);

};
}
#endif // LOGGER_H

