#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QDate>

#include <iostream>
EagleEye::DataHandler *DATA_HANDLER = nullptr;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(1, 1);
    setWindowTitle("EagleEye");
    DATA_HANDLER = new EagleEye::DataHandler();
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
    delete DATA_HANDLER;
    delete ui;
}

void MainWindow::DisplayImage(const QString &fileName)
{
    if (!DATA_HANDLER->InputImagePixMap().load(fileName))
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
    }

    ui->imageLabel->setPixmap(DATA_HANDLER->InputImagePixMap().scaled(ui->imageLabel->width(),
                                                        ui->imageLabel->height(),
                                                        Qt::KeepAspectRatio));
    ui->imageLabel->setAlignment(Qt::AlignCenter);
    ui->horizontalSlider->show();
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    ui->imageLabel->setPixmap(DATA_HANDLER->InputImagePixMap().scaled(ui->imageLabel->width(),
                                                        ui->imageLabel->height(),
                                                        Qt::KeepAspectRatio));

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    auto inputImageRect = DATA_HANDLER->InputImagePixMap().rect();
    QPainter panPainter;
    panPainter.drawImage(inputImageRect,DATA_HANDLER->InputImagePixMap().toImage());
    std::cout << e->x() << " " << e->y() << std::endl;
    update();

}

void MainWindow::Open()
{
    QString activeFileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "C:/", tr("Image Files (*.png *.jpg *.bmp)"));
    DATA_HANDLER->SetActiveFileName(activeFileName);
    QImageReader imageReader(activeFileName);
    QPixmap newPixMap = QPixmap::fromImageReader(&imageReader);
    DATA_HANDLER->SetInputImagePixMap(newPixMap);
    DisplayImage(activeFileName);
}

void MainWindow::SaveFileCopy()
{
    auto imageCopy = DATA_HANDLER->InputImagePixMap();
    imageCopy.save(QDate::currentDate().toString() + DATA_HANDLER->ActiveFileName());
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    float zoomFactor = static_cast<float>(value) / DATA_HANDLER->PreviousSliderValue();
    ui->imageLabel->setPixmap(DATA_HANDLER->InputImagePixMap().scaled(static_cast<int>(ui->imageLabel->width() * zoomFactor),
                                                        static_cast<int>(ui->imageLabel->height() * zoomFactor),
                                                        Qt::KeepAspectRatio));
}
