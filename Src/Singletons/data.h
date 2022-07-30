#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QObject>
#include <QPixmap>
#include <QMutex>
#include <QMutexLocker>
namespace EagleEye {

class Data
{
private:
    Data():
        m_ImageMutex(nullptr),
        m_CommonMutex(nullptr),
        m_ZoomFactor(1.0f),
        m_SelectROI(false)
    {

    }
public:
    static Data& SINGLE_INSTANCE(){
        static Data theInstance;
        return theInstance;
    }

    Data (const Data &) = delete;
    Data& operator=(const Data &) = delete;

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

    const QRect &GetRegionOfinterset() const;
    void SetRegionOfinterset(const QRect &newRegionOfinterset);

    const QPixmap &GetROIPixmap() const;
    void SetROIPixmap(const QPixmap &newROIPixmap);

    const QPixmap &GetImageLabelPixmap() const;
    void SetImageLabelPixmap(const QPixmap &newImageLabelPixmap);

    const QPixmap &GetImageToBeDisplayed() const;
    void SetImageToBeDisplayed(const QPixmap &newImageToBeDisplayed);

    float GetDisplayPixelLengthInMillimeter();

private:
    QPixmap m_InputImagePixMap;
    QPixmap m_DisplayedImagePixmap;
    QPixmap m_ImageLabelPixmap;
    QPixmap m_ROIPixmap;
    QPixmap m_ImageToBeDisplayed;
    QRect m_RegionOfinterset;
    QString m_ActiveFilePath;
    QMutex *m_ImageMutex;
    QMutex *m_CommonMutex;

    float m_ZoomFactor;
    bool m_SelectROI;
};
}
#endif // DATAHANDLER_H
