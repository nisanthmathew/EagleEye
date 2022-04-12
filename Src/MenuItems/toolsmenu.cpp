#include "toolsmenu.h"
#include "../Singletons/data.h"

namespace EagleEye
{
EEToolsMenu::EEToolsMenu(QMenu *parent)
    : QMenu{parent}
{
    m_ToolsMenu = parent;
    AddToolActions();
}

QList<QAction*> EEToolsMenu::AddToolActions()
{
    QAction *selectROI = new QAction(tr("&Select ROI"), this);
    m_ToolsMenu->addAction(selectROI);
    selectROI->setCheckable(true);
    connect(selectROI, &QAction::toggled, [](bool checked)
    {
        EagleEye::Data::SINGLE_INSTANCE().SetSelectROI(checked);

        if (!checked) //clear everything is unchecked
        {
            EagleEye::Data::SINGLE_INSTANCE().SetROIPixmap(QPixmap());
            EagleEye::Data::SINGLE_INSTANCE().SetRegionOfinterset(QRect());
        }

    });

    return m_ToolsMenu->actions();
}
}
