#ifndef FILEREADWRITE_H
#define FILEREADWRITE_H

#include <QObject>

class FileReadWrite : public QObject
{
    Q_OBJECT
public:
    FileReadWrite();
    ~FileReadWrite();

    bool SaveImageCopy();
};

#endif // FILEREADWRITE_H
