#include "fileMenu.h"
#include "../Singletons/data.h"
#include "../Singletons/logger.h"

namespace EagleEye
{
EEFileMenu::EEFileMenu(QMenu *parent)
    : QMenu{parent},
      m_ImageReadWrite(std::unique_ptr<EagleEye::ImageReadWrite>(new EagleEye::ImageReadWrite()))
{
    m_FileMenu = parent;
    AddFileActions();
}

QList<QAction*> EEFileMenu::AddFileActions()
{
    QAction *openAct = new QAction(tr("&Open"), this);
    m_FileMenu->addAction(openAct);
    connect(openAct, SIGNAL(triggered()), this, SLOT(Open()));

    QAction *copyAct = new QAction(tr("&Save Displayed Image"), this);
    m_FileMenu->addAction(copyAct);
    connect(copyAct, SIGNAL(triggered()), this, SLOT(SaveFileCopy()));

    return m_FileMenu->actions();
}

void EEFileMenu::Open()
{
    if (m_ImageReadWrite->EELoadImage())
    {
        const QString filePath {EagleEye::Data::SINGLE_INSTANCE().GetActiveFilePath()};
        emit DisplayImage();
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage(QString("MainWindow::Open(): loading image %1").arg(filePath),
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
    }
    else
    {
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::Open(): Failed to load image",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
    }
}

void EEFileMenu::SaveFileCopy()
{
    auto imageCopy = EagleEye::Data::SINGLE_INSTANCE().GetDisplayedImagePixmap();
    m_ImageReadWrite->EESaveImageCopy(imageCopy);
}

}
