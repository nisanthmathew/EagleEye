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

    QPixmap EELoadImage(QString &filePath);
    bool EESaveImageCopy(const QPixmap &imageToSave, QString filePath = "");
    QPixmap EELoadDicomImage(const QString &filePath);
};
}
#endif // IMAGEREADWRITE_H
