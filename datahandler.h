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
        m_ImageMutex(nullptr),
        m_CommonMutex(nullptr),
        m_PreviousSliderValue(100),
        m_SelectROI(false)
    {

    }
public:
    static DataHandler& DATA_HANDLER(){
        static DataHandler theInstance;
        return theInstance;
    }

    QPixmap GetOriginalImagePixmap() const;
    void SetInputImagePixmap(const QPixmap &inputImagePixMap);

    int GetPreviousSliderValue() const;
    void SetPreviousSliderValue(int previousSliderValue);

    QString GetActiveFilePath() const;
    void SetActiveFilePath(const QString &ActiveFilePath);

    const QPixmap &GetDisplayedImagePixmap() const;
    void SetDisplayedImagePixmap(const QPixmap &newDisplayedImagePixmap);

    const bool GetSelectROI() const;
    void SetSelectROI(const bool selectROI);

private:
    QPixmap m_InputImagePixMap;
    QPixmap m_DisplayedImagePixmap;
    QString m_ActiveFilePath;
    QMutex *m_ImageMutex;
    QMutex *m_CommonMutex;
    int m_PreviousSliderValue;
    bool m_SelectROI;
};
}
#endif // DATAHANDLER_H
