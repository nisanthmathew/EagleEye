#include <../Singletons/logger.h>

#include <QTest>
#include <QObject>

#include <chrono>
class LoggerTest : public QObject
{
    Q_OBJECT

public:
    LoggerTest();
    ~LoggerTest();

private slots:
    void LoggerPerfomanceTest();

};


LoggerTest::LoggerTest()
{

}

LoggerTest::~LoggerTest()
{

}


void LoggerTest::LoggerPerfomanceTest()
{
    QString testLog {"LoggerTest::LoggerPerfomanceTest(): testing, testing, testing."};
    std::string stdtestLog {"LoggerTest::LoggerPerfomanceTest(): testing, testing, testing."};
    QBENCHMARK
    {
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage(testLog.toStdString(), EagleEye::LOGLEVEL::EE_DEBUG);
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("LoggerTest::LoggerPerfomanceTest(): testing.", EagleEye::LOGLEVEL::EE_DEBUG);
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage(QString("LoggerTest::LoggerPerfomanceTest(): testing.").toStdString(), EagleEye::LOGLEVEL::EE_DEBUG);
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage(stdtestLog, EagleEye::LOGLEVEL::EE_DEBUG);
    }
}

QTEST_MAIN(LoggerTest)

#include "loggertest.moc"
