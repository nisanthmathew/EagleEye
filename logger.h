#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QDate>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>

#include <iostream>
#include <fstream>

namespace  EagleEye {
enum LOGLEVEL
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
    Logger()
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
            }
            m_LogVector.clear();
            logFileStream.close();
        });
        timer->start(100);
    }
    std::vector<std::string> m_LogVector;
    QMutex *m_LogMutex;

public:
    static Logger& CENTRAL_LOGGER(){
        static Logger theInstance;
        return theInstance;
    }
    void LogMessage(QString message, EagleEye::LOGLEVEL loglevel);
};
}
#endif // LOGGER_H

