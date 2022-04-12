#include "imageprocessingmenu.h"
#include "../Singletons/data.h"
#include "../Singletons/logger.h"
#include "../Utilities/imageprocessingutilities.h"

namespace EagleEye
{
EEImageProcessingMenu::EEImageProcessingMenu(QMenu *parent)
    : QMenu{parent}
{
    m_ImageProcessingMenu = parent;
    AddImageProcessingActions();
}

QList<QAction*> EEImageProcessingMenu::AddImageProcessingActions()
{
    QAction *greyScaleAction = new QAction(tr("&GreyScale"), this);
    m_ImageProcessingMenu->addAction(greyScaleAction);
    connect(greyScaleAction, &QAction::triggered, [this](bool checked)
    {
        ConvertDisplayFormat(EagleEye::DisplayFormats::GreyScale);
    });

    QAction *edgeDetectionAction = new QAction(tr("&Edge Detection"), this);
    m_ImageProcessingMenu->addAction(edgeDetectionAction);
    connect(edgeDetectionAction, &QAction::triggered, [this](bool checked)
    {
        ConvertDisplayFormat(EagleEye::DisplayFormats::Edge);
    });

    QAction *originalAction = new QAction(tr("&Original"), this);
    m_ImageProcessingMenu->addAction(originalAction);
    connect(originalAction, &QAction::triggered, [this](bool checked)
    {
        ConvertDisplayFormat(EagleEye::DisplayFormats::Original);
    });

    return m_ImageProcessingMenu->actions();
}

void EEImageProcessingMenu::ConvertDisplayFormat(EagleEye::DisplayFormats displayFormat)
{
    auto pixmapToBeProcessed = EagleEye::Data::SINGLE_INSTANCE().GetDisplayedImagePixmap();
    if (EagleEye::Data::SINGLE_INSTANCE().GetSelectROI()) // use ROI option select the use the ROI image
    {
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("EEImageProcessingMenu::ConvertDisplayFormat(): ROI is valid, hence using it.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        pixmapToBeProcessed = EagleEye::Data::SINGLE_INSTANCE().GetROIPixmap();
    }
    QPixmap imageToBeDisplayed;

    switch (displayFormat)
    {
    case EagleEye::DisplayFormats::GreyScale:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("EEImageProcessingMenu::ConvertDisplayFormat(): Converting to Greyscale.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        imageToBeDisplayed = CombineROIAndDisplayedPixmap(
                    ConvertRGBToGreyScale(pixmapToBeProcessed),
                    EagleEye::Data::SINGLE_INSTANCE().GetImageLabelPixmap());
        break;
    case EagleEye::DisplayFormats::Edge:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::ConvertDisplayFormat(): Converting to Edge.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        imageToBeDisplayed = EagleEye::CombineROIAndDisplayedPixmap(
                    EagleEye::ConvertRGBToEdges(pixmapToBeProcessed),
                    EagleEye::Data::SINGLE_INSTANCE().GetImageLabelPixmap());
        break;
    case EagleEye::DisplayFormats::Original:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("EEImageProcessingMenu::ConvertDisplayFormat(): Reverting to Greyscale.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        imageToBeDisplayed = EagleEye::Data::SINGLE_INSTANCE().GetOriginalImagePixmap();
        break;
    }

    EagleEye::Data::SINGLE_INSTANCE().SetImageToBeDisplayed(imageToBeDisplayed);
    emit ChangeDisplayedImage();
}
}
