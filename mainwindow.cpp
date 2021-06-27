#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QDate>

#include <iostream>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(1, 1);
    setWindowTitle("EagleEye");
    ui->horizontalSlider->setRange(100,400);
    ui->horizontalSlider->setTickInterval(1);
    ui->horizontalSlider->hide();

    QMenu *fileMenu;
    fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *openAct = new QAction(tr("&Open"), this);
    fileMenu->addAction(openAct);
    connect(openAct,SIGNAL(triggered()),this,SLOT(Open()));

    QAction *copyAct = new QAction(tr("&Save Copy"), this);
    fileMenu->addAction(copyAct);
    connect(copyAct,SIGNAL(triggered()),this,SLOT(SaveFileCopy()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisplayImage(const QString &fileName)
{
    if (!EagleEye::DataHandler::DATA_HANDLER().GetCurrentImagePixMap().load(fileName))
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
    }

    ui->imageLabel->setPixmap(EagleEye::DataHandler::DATA_HANDLER().GetCurrentImagePixMap().scaled(ui->imageLabel->width(),
                                                        ui->imageLabel->height(),
                                                        Qt::KeepAspectRatio));
    ui->imageLabel->setAlignment(Qt::AlignCenter);
    ui->horizontalSlider->show();
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    ui->imageLabel->setPixmap(EagleEye::DataHandler::DATA_HANDLER().GetCurrentImagePixMap().scaled(ui->imageLabel->width(),
                                                        ui->imageLabel->height(),
                                                        Qt::KeepAspectRatio));

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    auto inputImageRect = EagleEye::DataHandler::DATA_HANDLER().GetCurrentImagePixMap().rect();
    QPainter panPainter;
    panPainter.drawImage(inputImageRect,EagleEye::DataHandler::DATA_HANDLER().GetCurrentImagePixMap().toImage());
    QString message {QString("MainWindow::mousePressEvent(): Mouse x: %1, Mouse y: %2").arg(e->x()).arg(e->y())};
    EagleEye::Logger::CENTRAL_LOGGER().LogMessage(message,EagleEye::LOGLEVEL::DEBUG);
    update();

}

void MainWindow::Open()
{
    QString activeFileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "C:/", tr("Image Files (*.png *.jpg *.bmp)"));
    EagleEye::DataHandler::DATA_HANDLER().SetActiveFileName(activeFileName);
    QImageReader imageReader(activeFileName);
    QPixmap newPixMap = QPixmap::fromImageReader(&imageReader);
    EagleEye::DataHandler::DATA_HANDLER().SetCurrentImagePixMap(newPixMap);
    DisplayImage(activeFileName);
}

void MainWindow::SaveFileCopy()
{
    auto imageCopy = EagleEye::DataHandler::DATA_HANDLER().GetCurrentImagePixMap();
    if (imageCopy.isNull())
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("There is no image to save."));
        return;
    }
    auto newFileName = QDate::currentDate().toString() + EagleEye::DataHandler::DATA_HANDLER().GetActiveFileName();
    if (!imageCopy.save(newFileName))
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Unable to save image."));
    }
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    float zoomFactor = static_cast<float>(value) / EagleEye::DataHandler::DATA_HANDLER().GetPreviousSliderValue();
    ui->imageLabel->setPixmap(EagleEye::DataHandler::DATA_HANDLER().GetCurrentImagePixMap().scaled(static_cast<int>(ui->imageLabel->width() * zoomFactor),
                                                        static_cast<int>(ui->imageLabel->height() * zoomFactor),
                                                        Qt::KeepAspectRatio));
}
