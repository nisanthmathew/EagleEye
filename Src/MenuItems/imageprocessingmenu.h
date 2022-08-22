#ifndef IMAGEPROCESSINGMENU_H
#define IMAGEPROCESSINGMENU_H

#include <QMenu>
#include <QAction>

namespace EagleEye
{

class ImageViewController;
enum class DisplayFormats;

class EEImageProcessingMenu : public QMenu
{
    Q_OBJECT
public:
    explicit EEImageProcessingMenu(QMenu *parent = nullptr, EagleEye::ImageViewController *controller = nullptr);

signals:
    void ConvertImageDisplayFormat(EagleEye::DisplayFormats displayFormat);

private:
    void AddImageProcessingActions();
    QMenu *m_ImageProcessingMenu;
    EagleEye::ImageViewController *m_ImageViewController;
};
}
#endif // IMAGEPROCESSINGMENU_H
