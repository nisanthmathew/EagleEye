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
    m_ImageReadWrite = std::unique_ptr<EagleEye::ImageReadWrite>(new EagleEye::ImageReadWrite());

    AddFileMenu();
    AddToolsMenu();
    AddDisplayFormats();
}

MainWindow::~MainWindow()
{
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

void MainWindow::DisplayPixmap(const QPixmap &pixmap)
{
    EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::DisplayPixmap(): Setting and displaying pixmap.",
                                                  EagleEye::LOGLEVEL::EE_DEBUG);
    EagleEye::DataHandler::SINGLE_INSTANCE().SetDisplayedImagePixmap(pixmap);
    ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->width(), ui->imageLabel->height(),
                                            Qt::KeepAspectRatio));
    ui->imageLabel->setAlignment(Qt::AlignCenter);
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

    ui->imageLabel->setPixmap(EagleEye::DataHandler::SINGLE_INSTANCE().GetDisplayedImagePixmap().scaled(
                                  static_cast<int>(ui->imageLabel->width() * zoomFactor),
                                  static_cast<int>(ui->imageLabel->height() * zoomFactor),
                                  Qt::KeepAspectRatio));
    EagleEye::DataHandler::SINGLE_INSTANCE().SetZoomFactor(zoomFactor);
}

void MainWindow::AddFileMenu()
{
    QMenu *fileMenu;
    fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAct = new QAction(tr("&Open"), this);
    fileMenu->addAction(openAct);
    connect(openAct, SIGNAL(triggered()), this, SLOT(Open()));

    QAction *copyAct = new QAction(tr("&Save Displayed Image"), this);
    fileMenu->addAction(copyAct);
    connect(copyAct, SIGNAL(triggered()), this, SLOT(SaveFileCopy()));
}

void MainWindow::AddToolsMenu()
{
    QMenu *toolMenu;
    toolMenu = menuBar()->addMenu(tr("&Tools"));
    QAction *selectROI = new QAction(tr("&Select ROI"), this);
    toolMenu->addAction(selectROI);
    selectROI->setCheckable(true);
    connect(selectROI, &QAction::toggled, [this, &selectROI](bool checked)
    {
        EagleEye::DataHandler::SINGLE_INSTANCE().SetSelectROI(checked);

        if (!checked) //clear everything is unchecked
        {
            EagleEye::DataHandler::SINGLE_INSTANCE().SetROIPixmap(QPixmap());
            EagleEye::DataHandler::SINGLE_INSTANCE().SetRegionOfinterset(QRect());
        }

    });
}

void MainWindow::AddDisplayFormats()
{
    QMenu *DisplayFormats;
    DisplayFormats = menuBar()->addMenu("&Display Formats");

    QAction *greyScaleAction = new QAction(tr("&GreyScale"), this);
    DisplayFormats->addAction(greyScaleAction);
    connect(greyScaleAction, &QAction::triggered, [this](bool checked)
    {
        ConvertDisplayFormat(EagleEye::DisplayFormats::GreyScale);
    });

    QAction *edgeDetectionAction = new QAction(tr("&Edge Detection"), this);
    DisplayFormats->addAction(edgeDetectionAction);
    connect(edgeDetectionAction, &QAction::triggered, [this](bool checked)
    {
        ConvertDisplayFormat(EagleEye::DisplayFormats::Edge);
    });

    QAction *originalAction = new QAction(tr("&Original"), this);
    DisplayFormats->addAction(originalAction);
    connect(originalAction, &QAction::triggered, [this](bool checked)
    {
        ConvertDisplayFormat(EagleEye::DisplayFormats::Original);
    });
}

void MainWindow::Open()
{
    if (m_ImageReadWrite->EELoadImage())
    {
        const QString filePath {EagleEye::DataHandler::SINGLE_INSTANCE().GetActiveFilePath()};
        DisplayImage(filePath);
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage(QString("MainWindow::Open(): loading image %1").arg(filePath),
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
    }
    else
    {
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::Open(): Failed to load image",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
    }
}

void MainWindow::SaveFileCopy()
{
    auto imageCopy = EagleEye::DataHandler::SINGLE_INSTANCE().GetDisplayedImagePixmap();
    m_ImageReadWrite->EESaveImageCopy(imageCopy);
}

void MainWindow::ConvertDisplayFormat(EagleEye::DisplayFormats displayFormat)
{
    if (m_Rubberband)
    {
        m_Rubberband->hide();
    }

    auto pixmapToBeProcessed = EagleEye::DataHandler::SINGLE_INSTANCE().GetDisplayedImagePixmap();
    if (EagleEye::DataHandler::SINGLE_INSTANCE().GetSelectROI()) // use ROI option select the use the ROI image
    {
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::ConvertDisplayFormat(): ROI is valid, hence using it.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        pixmapToBeProcessed = EagleEye::DataHandler::SINGLE_INSTANCE().GetROIPixmap();
    }

    switch (displayFormat)
    {
    case EagleEye::DisplayFormats::GreyScale:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::ConvertDisplayFormat(): Converting to Greyscale.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        DisplayPixmap(EagleEye::CombineROIAndDisplayedPixmap(
                          EagleEye::ConvertRGBToGreyScale(pixmapToBeProcessed), ui->imageLabel->pixmap(Qt::ReturnByValue)));
        break;
    case EagleEye::DisplayFormats::Edge:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::ConvertDisplayFormat(): Converting to Edge.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        DisplayPixmap(EagleEye::CombineROIAndDisplayedPixmap(
                          EagleEye::ConvertRGBToEdges(pixmapToBeProcessed), ui->imageLabel->pixmap(Qt::ReturnByValue)));
        break;
    case EagleEye::DisplayFormats::Original:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::ConvertDisplayFormat(): Reverting to Greyscale.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        DisplayPixmap(EagleEye::DataHandler::SINGLE_INSTANCE().GetOriginalImagePixmap());
        break;
    }
}

QPoint MainWindow::MapPointToPixmap(QPoint point, QPixmap *pixmap)
{
    auto mappedPoint = ui->imageLabel->mapFrom(this, point);
    mappedPoint.setX(point.x() - int((ui->imageLabel->width() - pixmap->width()) / 2));
    mappedPoint.setY(point.y() - int((ui->imageLabel->height() - pixmap->height()) / 2));
    return mappedPoint;
}
