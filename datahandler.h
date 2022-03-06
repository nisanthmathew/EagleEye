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
        m_ZoomFactor(1.0f),
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

    QString GetActiveFilePath() const;
    void SetActiveFilePath(const QString &ActiveFilePath);

    const QPixmap &GetDisplayedImagePixmap() const;
    void SetDisplayedImagePixmap(const QPixmap &newDisplayedImagePixmap);

    const bool GetSelectROI() const;
    void SetSelectROI(const bool selectROI);

    float GetZoomFactor() const;
    void SetZoomFactor(float newZoomFactor);

private:
    QPixmap m_InputImagePixMap;
    QPixmap m_DisplayedImagePixmap;
    QString m_ActiveFilePath;
    QMutex *m_ImageMutex;
    QMutex *m_CommonMutex;
    float m_ZoomFactor;
    bool m_SelectROI;
};
}
#endif // DATAHANDLER_H
