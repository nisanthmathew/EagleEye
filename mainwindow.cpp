#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QDate>

#include <iostream>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Rubberband(nullptr)
{
    ui->setupUi(this);
    setMinimumSize(1, 1);
    setWindowTitle("EagleEye");
    ui->horizontalSlider->setRange(100,400);
    ui->horizontalSlider->setTickInterval(1);
    ui->horizontalSlider->hide();
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
    if (!EagleEye::DataHandler::DATA_HANDLER().GetOriginalImagePixmap().load(fileName))
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
    }

    DisplayPixmap(EagleEye::DataHandler::DATA_HANDLER().GetOriginalImagePixmap());
}

void MainWindow::DisplayPixmap(const QPixmap &pixmap)
{
    EagleEye::DataHandler::DATA_HANDLER().SetDisplayedImagePixmap(pixmap);
    ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->width(), ui->imageLabel->height(),
                                            Qt::KeepAspectRatio));
    ui->imageLabel->setAlignment(Qt::AlignCenter);
    ui->horizontalSlider->show();
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    ui->imageLabel->setPixmap(EagleEye::DataHandler::DATA_HANDLER().GetDisplayedImagePixmap().scaled(ui->imageLabel->width(),
                                                        ui->imageLabel->height(),
                                                        Qt::KeepAspectRatio));
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (EagleEye::DataHandler::DATA_HANDLER().GetSelectROI())
    {
        m_MouseStartPoint = e->pos();
        if (!m_Rubberband)
            m_Rubberband = new QRubberBand(QRubberBand::Rectangle, this);
        m_Rubberband->setGeometry(QRect(m_MouseStartPoint, QSize(0,0)));
        m_Rubberband->show();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (EagleEye::DataHandler::DATA_HANDLER().GetSelectROI() && m_Rubberband)
    {
        m_Rubberband->setGeometry(QRect(m_MouseStartPoint, e->pos()).normalized());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (EagleEye::DataHandler::DATA_HANDLER().GetSelectROI() && m_Rubberband)
    {
        QPixmap displayedPixmap = ui->imageLabel->pixmap(Qt::ReturnByValue);
        auto mappedStartPoint = ui->imageLabel->mapFrom(this, m_MouseStartPoint);
        auto x = mappedStartPoint.x() - int((ui->imageLabel->width() - displayedPixmap.width()) / 2);
        auto y = mappedStartPoint.y() - int((ui->imageLabel->height() - displayedPixmap.height()) / 2);
        auto croppedImage = displayedPixmap.copy(x, y, m_Rubberband->geometry().width(), m_Rubberband->geometry().height());
        DisplayPixmap(croppedImage);
        m_Rubberband->hide();
    }
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
        EagleEye::DataHandler::DATA_HANDLER().SetSelectROI(checked);
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
        const QString filePath {EagleEye::DataHandler::DATA_HANDLER().GetActiveFilePath()};
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
    auto imageCopy = EagleEye::DataHandler::DATA_HANDLER().GetDisplayedImagePixmap();
    m_ImageReadWrite->EESaveImageCopy(imageCopy);
}

void MainWindow::ConvertDisplayFormat(EagleEye::DisplayFormats displayFormat)
{
    switch (displayFormat)
    {
    case EagleEye::DisplayFormats::GreyScale:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::ConvertDisplayFormat(): Converting to Greyscale",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        DisplayPixmap(EagleEye::ConvertRGBToGreyScale(EagleEye::DataHandler::DATA_HANDLER().GetDisplayedImagePixmap()));
        break;
    case EagleEye::DisplayFormats::Edge:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::ConvertDisplayFormat(): Converting to Edge",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        DisplayPixmap(EagleEye::ConvertRGBToEdges(EagleEye::DataHandler::DATA_HANDLER().GetDisplayedImagePixmap()));
        break;
    case EagleEye::DisplayFormats::Original:
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::ConvertDisplayFormat(): Reverting to Greyscale",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        DisplayPixmap(EagleEye::DataHandler::DATA_HANDLER().GetOriginalImagePixmap());
        break;
    }
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    float zoomFactor = static_cast<float>(value) / EagleEye::DataHandler::DATA_HANDLER().GetPreviousSliderValue();
    ui->imageLabel->setPixmap(EagleEye::DataHandler::DATA_HANDLER().GetDisplayedImagePixmap().scaled(
                                  static_cast<int>(ui->imageLabel->width() * zoomFactor),
                                  static_cast<int>(ui->imageLabel->height() * zoomFactor),
                                  Qt::KeepAspectRatio));
}
