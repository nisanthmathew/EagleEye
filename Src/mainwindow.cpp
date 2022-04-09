#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eeroiqrubberband.h"

#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QDate>
#include <QRubberBand>

#include <iostream>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Rubberband(nullptr)
{
    ui->setupUi(this);
    setMinimumSize(1, 1);
    setWindowTitle("EagleEye");


    m_FileMenu = new EagleEye::EEFileMenu(menuBar()->addMenu("&File"));
    connect(m_FileMenu, SIGNAL(DisplayImage(QString)), this, SLOT(DisplayImage(QString)));

    m_ToolsMenu = new EagleEye::EEToolsMenu(menuBar()->addMenu("&Tools"));

    m_ImageProcessingMenu = new EagleEye::EEImageProcessingMenu(menuBar()->addMenu("&Image Processing"));
    connect(m_ImageProcessingMenu, SIGNAL(ChangeDisplayedImage()), this, SLOT(DisplayPixmap()));
}

MainWindow::~MainWindow()
{
    delete m_FileMenu;
    delete m_ToolsMenu;
    delete m_ImageProcessingMenu;
    delete ui;
}

void MainWindow::DisplayImage(const QString &fileName)
{
    if (!EagleEye::DataHandler::SINGLE_INSTANCE().GetOriginalImagePixmap().load(fileName))
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
    }

    DisplayPixmap(EagleEye::DataHandler::SINGLE_INSTANCE().GetOriginalImagePixmap());
}

void MainWindow::DisplayPixmap()
{
    if (m_Rubberband)//hiding ROI
    {
        m_Rubberband->hide();
    }

    DisplayPixmap(EagleEye::DataHandler::SINGLE_INSTANCE().GetImageToBeDisplayed());
}

void MainWindow::DisplayPixmap(const QPixmap &pixmap, const float &zoomFactor)
{
    EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::DisplayPixmap(): Setting and displaying pixmap.",
                                                  EagleEye::LOGLEVEL::EE_DEBUG);
    EagleEye::DataHandler::SINGLE_INSTANCE().SetDisplayedImagePixmap(pixmap);
    ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->width() * zoomFactor, ui->imageLabel->height() * zoomFactor,
                                            Qt::KeepAspectRatio));
    ui->imageLabel->setAlignment(Qt::AlignCenter);
    EagleEye::DataHandler::SINGLE_INSTANCE().SetImageLabelPixmap(ui->imageLabel->pixmap(Qt::ReturnByValue));
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    ui->imageLabel->setPixmap(EagleEye::DataHandler::SINGLE_INSTANCE().GetDisplayedImagePixmap().scaled(ui->imageLabel->width(),
                                                                                                        ui->imageLabel->height(),
                                                                                                        Qt::KeepAspectRatio));
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    m_MouseStartPoint = ui->imageLabel->mapFrom(this, e->pos());
    if (EagleEye::DataHandler::SINGLE_INSTANCE().GetSelectROI())
    {
        if (!m_Rubberband)
        {
            m_Rubberband = std::unique_ptr<EEROIQRubberBand>(new EEROIQRubberBand(QRubberBand::Rectangle, ui->imageLabel));
        }
        m_Rubberband->setGeometry(QRect(m_MouseStartPoint, QSize(0,0)));
        m_Rubberband->show();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (EagleEye::DataHandler::SINGLE_INSTANCE().GetSelectROI() && m_Rubberband)
    {
        m_Rubberband->setGeometry(QRect(m_MouseStartPoint, ui->imageLabel->mapFrom(this, e->pos())).normalized());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (EagleEye::DataHandler::SINGLE_INSTANCE().GetSelectROI() && m_Rubberband)
    {
        const auto rubberbandGeometry = m_Rubberband->geometry();
        QPixmap displayedPixmap = ui->imageLabel->pixmap(Qt::ReturnByValue);
        const auto topLeft = MapPointToPixmap(rubberbandGeometry.topLeft(), &displayedPixmap);
        const auto bottomRight = MapPointToPixmap(rubberbandGeometry.bottomRight(), &displayedPixmap);
        QRect ROI (topLeft, bottomRight);
        EagleEye::DataHandler::SINGLE_INSTANCE().SetRegionOfinterset(ROI);
        EagleEye::DataHandler::SINGLE_INSTANCE().SetROIPixmap(displayedPixmap.copy(ROI));
    }
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
    if (m_Rubberband)
    {
        m_Rubberband->hide();
    }

    int zoomDir = e->angleDelta().y() / std::abs(e->angleDelta().y());
    float zoomFactor = EagleEye::DataHandler::SINGLE_INSTANCE().GetZoomFactor() + (zoomDir * 0.1);

    if (zoomFactor >= 5.0 || zoomFactor <= 0.5) //zoom out is permitted only till half size and zoom in for 4 times the size
        return;

    DisplayPixmap(EagleEye::DataHandler::SINGLE_INSTANCE().GetDisplayedImagePixmap(), zoomFactor);
    EagleEye::DataHandler::SINGLE_INSTANCE().SetZoomFactor(zoomFactor);
}

QPoint MainWindow::MapPointToPixmap(QPoint point, QPixmap *pixmap)
{
    auto mappedPoint = ui->imageLabel->mapFrom(this, point);
    mappedPoint.setX(point.x() - int((ui->imageLabel->width() - pixmap->width()) / 2));
    mappedPoint.setY(point.y() - int((ui->imageLabel->height() - pixmap->height()) / 2));
    return mappedPoint;
}
