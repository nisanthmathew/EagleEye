#ifndef EEFLIEMENU_H
#define EEFLIEMENU_H

#include "../Utilities/imagereadwriteutilities.h"

#include <QMenu>
#include <QAction>

namespace EagleEye
{
class EEFileMenu : public QMenu
{
    Q_OBJECT
public:
    explicit EEFileMenu(QMenu *parent = nullptr);

signals:
    void DisplayImage();

private slots:
    void Open();
    void SaveFileCopy();

private:
    QList<QAction *> AddFileActions();
    QMenu *m_FileMenu;
    std::unique_ptr<EagleEye::ImageReadWrite> m_ImageReadWrite;
    QAction *m_SelectROI;
};
}
#endif // EEFLIEMENU_H
