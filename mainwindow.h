#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "datahandler.h"
#include "logger.h"
#include "Tools/imagereadwrite.h"
#include "Tools/displayformat.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QImageReader>
#include <QAction>
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
    void Open();
    void SaveFileCopy();
    void ConvertDisplayFormat(EagleEye::DisplayFormats displayFormat);

private:
    void DisplayImage(const QString &fileName);
    void DisplayPixmap(const QPixmap &pixmap);
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    void AddFileMenu();
    void AddToolsMenu();
    void AddDisplayFormats();

    Ui::MainWindow *ui;
    std::unique_ptr<EEROIQRubberBand> m_Rubberband;
    std::unique_ptr<EagleEye::ImageReadWrite> m_ImageReadWrite;
    QPoint m_MouseStartPoint;
};
#endif // MAINWINDOW_H
