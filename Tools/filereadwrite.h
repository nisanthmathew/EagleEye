#ifndef FILEREADWRITE_H
#define FILEREADWRITE_H

#include <QObject>
namespace EagleEye{
class FileReadWrite : public QObject
{
    Q_OBJECT
public:
    FileReadWrite();
    ~FileReadWrite();

    bool SaveImageCopy(const QPixmap &imageToSave);
};
}
#endif // FILEREADWRITE_H
