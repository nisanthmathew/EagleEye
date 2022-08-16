#ifndef EEFLIEMENU_H
#define EEFLIEMENU_H

#include "../Utilities/imagereadwriteutilities.h"
#include "../Singletons/imageviewcontroller.h"

#include <QMenu>
#include <QAction>

namespace EagleEye
{
class EEFileMenu : public QMenu
{
    Q_OBJECT
public:
    explicit EEFileMenu(QMenu *parent = nullptr, EagleEye::ImageViewController *controller = nullptr);

private:
    QList<QAction *> AddFileActions();
    QMenu *m_FileMenu;
    std::unique_ptr<EagleEye::ImageReadWrite> m_ImageReadWrite;
    QAction *m_SelectROI;
    EagleEye::ImageViewController *m_ImageViewController;
};
}
#endif // EEFLIEMENU_H
