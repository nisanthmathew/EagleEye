#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QObject>
#include <QPixmap>
#include <QMutex>
#include <QMutexLocker>
namespace EagleEye {

class DataHandler
{
private:
    DataHandler():
        m_PreviousSliderValue(100)
    {

    }
public:
    static DataHandler& DATA_HANDLER(){
        static DataHandler theInstance;
        return theInstance;
    }

    QPixmap GetCurrentImagePixMap() const;
    void SetCurrentImagePixMap(const QPixmap &CurrentImagePixMap);

    int GetPreviousSliderValue() const;
    void SetPreviousSliderValue(int previousSliderValue);

    QString GetActiveFileName() const;
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
