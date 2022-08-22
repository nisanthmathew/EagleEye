#ifndef IMAGEVIEWCONTROLLER_H
#define IMAGEVIEWCONTROLLER_H

#include <QObject>

class QLabel;

namespace EagleEye {

//forward declarations
class ImageModel;
enum class DisplayFormats;

class ImageViewController : public QObject
{
    Q_OBJECT
public:
    explicit ImageViewController(QObject *parent = nullptr, EagleEye::ImageModel *model = nullptr);

    EagleEye::ImageModel *GetImageModel() const;

    void SetRectangularROI(const QRect &ROI);

public slots:
    void ConvertImageDisplayFormat(EagleEye::DisplayFormats displayFormat);
    void OpenImage();
    void SaveImageCopy();
    void SelectRectangularROI(bool startSelecting);

private:
    bool eventFilter(QObject *object, QEvent *e) override;
    EagleEye::ImageModel *m_ImageModel;
    QLabel *m_ImageViewLabel;

};
}
#endif // IMAGEVIEWCONTROLLER_H
