#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

namespace EagleEye {
class Logger;
class ImageModel;
class ImageViewController;
class EEToolsMenu;
class EEFileMenu;
class EEImageProcessingMenu;
class EEROIQRubberBand;
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void OnImageModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    QPoint MapPointToPixmap(QPoint point, QPixmap *pixmap);

    Ui::MainWindow *ui;
    EagleEye::ImageModel *m_ImageModel;
    EagleEye::ImageViewController *m_ImageViewController;
    EagleEye::EEFileMenu *m_FileMenu;
    EagleEye::EEToolsMenu *m_ToolsMenu;
    EagleEye::EEImageProcessingMenu* m_ImageProcessingMenu;
    EagleEye::EEROIQRubberBand *m_RectangularSelectedRegion;
    QPoint m_MouseStartPoint;
};
#endif // MAINWINDOW_H
