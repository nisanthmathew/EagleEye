#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QObject>
#include <QPixmap>
#include <QMutex>
#include <QMutexLocker>
namespace EagleEye {

class DataHandler
{
public:
    DataHandler();

    QPixmap InputImagePixMap() const;
    void SetInputImagePixMap(const QPixmap &InputImagePixMap);

    int PreviousSliderValue() const;
    void SetPreviousSliderValue(int previousSliderValue);

    QString ActiveFileName() const;
    void SetActiveFileName(const QString &ActiveFileName);

private:
    QPixmap m_InputImagePixMap;
    QString m_ActiveFileName;
    int m_PreviousSliderValue;
    QMutex *m_CommonMutex;
    QMutex *m_ImageMutex;
};

#endif // DATAHANDLER_H
}
