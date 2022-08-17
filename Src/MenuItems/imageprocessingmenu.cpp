#include "imageprocessingmenu.h"
#include "../Singletons/logger.h"
#include "../Utilities/imageprocessingutilities.h"

namespace EagleEye
{
EEImageProcessingMenu::EEImageProcessingMenu(QMenu *parent, EagleEye::ImageViewController *controller)
    : QMenu{parent},
      m_ImageViewController(controller)
{
    m_ImageProcessingMenu = parent;
    connect(this, &EEImageProcessingMenu::ConvertImageDisplayFormat, m_ImageViewController, &ImageViewController::ConvertImageDisplayFormat);
    AddImageProcessingActions();
}

void EEImageProcessingMenu::AddImageProcessingActions()
{
    QAction *greyScaleAction = new QAction(tr("&GreyScale"), this);
    m_ImageProcessingMenu->addAction(greyScaleAction);
    connect(greyScaleAction, &QAction::triggered, [this](bool checked)
    {
        emit ConvertImageDisplayFormat(EagleEye::DisplayFormats::GreyScale);
    });

    QAction *edgeDetectionAction = new QAction(tr("&Edge Detection"), this);
    m_ImageProcessingMenu->addAction(edgeDetectionAction);
    connect(edgeDetectionAction, &QAction::triggered, [this](bool checked)
    {
        emit ConvertImageDisplayFormat(EagleEye::DisplayFormats::Edge);
    });

    QAction *originalAction = new QAction(tr("&Original"), this);
    m_ImageProcessingMenu->addAction(originalAction);
    connect(originalAction, &QAction::triggered, [this](bool checked)
    {
        emit ConvertImageDisplayFormat(EagleEye::DisplayFormats::Original);
    });
}


}
