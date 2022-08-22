#include "toolsmenu.h"

#include <../Singletons/imageviewcontroller.h>

namespace EagleEye
{
EEToolsMenu::EEToolsMenu(QMenu *parent, EagleEye::ImageViewController *controller)
    : QMenu{parent},
      m_ImageViewController(controller)
{
    m_ToolsMenu = parent;
    AddToolActions();

}

QList<QAction*> EEToolsMenu::AddToolActions()
{
    QAction *selectROI = new QAction(tr("&Select ROI"), this);
    m_ToolsMenu->addAction(selectROI);
    selectROI->setCheckable(true);
    connect(selectROI, &QAction::toggled, m_ImageViewController, &ImageViewController::SelectRectangularROI);

    return m_ToolsMenu->actions();
}
}
