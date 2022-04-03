#ifndef IMAGEREADWRITE_H
#define IMAGEREADWRITE_H

#include <QtWidgets/QWidget>
namespace EagleEye
{
class ImageReadWrite : public QWidget
{
    Q_OBJECT
public:
    explicit ImageReadWrite(QWidget *parent = nullptr);

    bool EELoadImage();
    bool EESaveImageCopy(const QPixmap &imageToSave);

};
}
#endif // IMAGEREADWRITE_H
