#ifndef IMAGEVIEWCONTROLLER_H
#define IMAGEVIEWCONTROLLER_H

#include <QObject>
#include <../Singletons/imagemodel.h>
#include <../Utilities/displayformatutilities.h>

namespace EagleEye {
class ImageModel;

class ImageViewController : public QObject
{
    Q_OBJECT
public:
    explicit ImageViewController(QObject *parent = nullptr, EagleEye::ImageModel *model = nullptr);

    EagleEye::ImageModel *GetImageModel() const;

public slots:
    void ConvertImageDisplayFormat(EagleEye::DisplayFormats displayFormat);
    void OpenImage();
    void SaveImageCopy();

private:
    bool eventFilter(QObject *object, QEvent *e) override;
    EagleEye::ImageModel *m_ImageModel;

};
}
#endif // IMAGEVIEWCONTROLLER_H
