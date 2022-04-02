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
    static DataHandler& SINGLE_INSTANCE(){
        static DataHandler theInstance;
        return theInstance;
    }

    DataHandler (const DataHandler &) = delete;
    DataHandler& operator=(const DataHandler &) = delete;

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

    const QVector<QPoint> &GetRegionOfinterset() const;
    void SetRegionOfinterset(const QVector<QPoint> &newRegionOfinterset);

private:
    QPixmap m_InputImagePixMap;
    QPixmap m_DisplayedImagePixmap;
    QVector<QPoint> m_RegionOfinterset;
    QString m_ActiveFilePath;
    QMutex *m_ImageMutex;
    QMutex *m_CommonMutex;
    float m_ZoomFactor;
    bool m_SelectROI;
};
}
#endif // DATAHANDLER_H
