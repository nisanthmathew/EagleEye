#include "toolsmenu.h"
#include "../datahandler.h"

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
        EagleEye::DataHandler::SINGLE_INSTANCE().SetSelectROI(checked);

        if (!checked) //clear everything is unchecked
        {
            EagleEye::DataHandler::SINGLE_INSTANCE().SetROIPixmap(QPixmap());
            EagleEye::DataHandler::SINGLE_INSTANCE().SetRegionOfinterset(QRect());
        }

    });

    return m_ToolsMenu->actions();
}
}
