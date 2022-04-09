#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "datahandler.h"
#include "logger.h"
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
    void DisplayPixmap();
    void DisplayImage(const QString &fileName);

private:
    void DisplayPixmap(const QPixmap &pixmap, const float &zoomFactor = 1.0);
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    QPoint MapPointToPixmap(QPoint point, QPixmap *pixmap);

    Ui::MainWindow *ui;
    EagleEye::EEToolsMenu *m_ToolsMenu;
    EagleEye::EEFileMenu *m_FileMenu;
    EagleEye::EEImageProcessingMenu* m_ImageProcessingMenu;
    std::unique_ptr<EEROIQRubberBand> m_Rubberband;
    QPoint m_MouseStartPoint;
};
#endif // MAINWINDOW_H
