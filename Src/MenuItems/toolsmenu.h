#ifndef EETOOLSMENU_H
#define EETOOLSMENU_H

#include <QMenu>
#include <QAction>

namespace EagleEye
{

class ImageViewController;

class EEToolsMenu : public QMenu
{
    Q_OBJECT
public:
    explicit EEToolsMenu(QMenu *parent = nullptr, EagleEye::ImageViewController *controller = nullptr);

private:
    QList<QAction *> AddToolActions();
    QMenu *m_ToolsMenu;
    EagleEye::ImageViewController *m_ImageViewController;
};
}
#endif // EETOOLSMENU_H
