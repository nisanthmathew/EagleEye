#ifndef EETOOLSMENU_H
#define EETOOLSMENU_H

#include <QMenu>
#include <QAction>

namespace EagleEye
{
class EEToolsMenu : public QMenu
{
    Q_OBJECT
public:
    explicit EEToolsMenu(QMenu *parent = nullptr);

private:
    QList<QAction *> AddToolActions();
    QMenu *m_ToolsMenu;
};
}
#endif // EETOOLSMENU_H
