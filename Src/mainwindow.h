#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Singletons/data.h"
#include "Singletons/logger.h"
#include "Singletons/imagemodel.h"
#include "Singletons/imageviewcontroller.h"
#include "Utilities/imagereadwriteutilities.h"
#include "Utilities/displayformatutilities.h"
#include "MenuItems/toolsmenu.h"
#include "MenuItems/fileMenu.h"
#include "MenuItems/imageprocessingmenu.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QImageReader>
#include <QResizeEvent>

#include <memory>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class EEROIQRubberBand;

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
    void wheelEvent(QWheelEvent *e) override;
    QPoint MapPointToPixmap(QPoint point, QPixmap *pixmap);

    Ui::MainWindow *ui;
    EagleEye::ImageModel *m_ImageModel;
    EagleEye::ImageViewController *m_ImageViewController;
    EagleEye::EEToolsMenu *m_ToolsMenu;
    EagleEye::EEFileMenu *m_FileMenu;
    EagleEye::EEImageProcessingMenu* m_ImageProcessingMenu;
    std::unique_ptr<EEROIQRubberBand> m_Rubberband;
    QPoint m_MouseStartPoint;
};
#endif // MAINWINDOW_H
