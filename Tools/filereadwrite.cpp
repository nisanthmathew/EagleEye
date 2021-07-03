#include "filereadwrite.h"
#include "../logger.h"

#include <QPixmap>
#include <QString>

namespace EagleEye
{

FileReadWrite::FileReadWrite()
{

}

FileReadWrite::~FileReadWrite()
{

}

bool FileReadWrite::SaveImageCopy(const QPixmap &imageToSave)
{
    if (imageToSave.isNull())
    {
        return  false;
    }
    return true;
}
}
