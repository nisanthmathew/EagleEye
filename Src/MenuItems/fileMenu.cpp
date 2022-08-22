#include "fileMenu.h"

#include "../Singletons/logger.h"
#include "../Singletons/imageviewcontroller.h"

namespace EagleEye
{
EEFileMenu::EEFileMenu(QMenu *parent, EagleEye::ImageViewController *controller)
    : QMenu{parent},
      m_ImageViewController(controller),
      m_ImageReadWrite(std::unique_ptr<EagleEye::ImageReadWrite>(new EagleEye::ImageReadWrite()))
{
    m_FileMenu = parent;
    AddFileActions();
}

QList<QAction*> EEFileMenu::AddFileActions()
{
    QAction *openAct = new QAction(tr("&Open"), this);
    m_FileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, m_ImageViewController, &ImageViewController::OpenImage);


    QAction *copyAct = new QAction(tr("&Save Displayed Image"), this);
    m_FileMenu->addAction(copyAct);
    connect(copyAct, &QAction::triggered, m_ImageViewController, &ImageViewController::SaveImageCopy);

    return m_FileMenu->actions();
}
}
