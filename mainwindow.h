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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void DisplayImage(const QString &fileName);
    void DisplayPixmap(const QPixmap &pixmap);
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseDragEvent(QMouseEvent *e);

public slots:
    void Open();
    void SaveFileCopy();
    void ConvertDisplayFormat(EagleEye::DisplayFormats displayFormat);

private slots:
    void on_horizontalSlider_valueChanged(int value);

private:
    void AddToolsMenu();
    void AddFileMenu();

    Ui::MainWindow *ui;
    std::unique_ptr<EagleEye::ImageReadWrite> m_ImageReadWrite;
};
#endif // MAINWINDOW_H
