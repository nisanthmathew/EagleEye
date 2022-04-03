#ifndef IMAGEPROCESSINGMENU_H
#define IMAGEPROCESSINGMENU_H

#include "../Utilities/displayformatutilities.h"

#include <QMenu>
#include <QAction>

namespace EagleEye
{
class EEImageProcessingMenu : public QMenu
{
    Q_OBJECT
public:
    explicit EEImageProcessingMenu(QMenu *parent = nullptr);

signals:
    void ChangeDisplayedImage();

private:
    QList<QAction *> AddImageProcessingActions();
    void ConvertDisplayFormat(EagleEye::DisplayFormats displayFormat);
    QMenu *m_ImageProcessingMenu;
};
}
#endif // IMAGEPROCESSINGMENU_H
