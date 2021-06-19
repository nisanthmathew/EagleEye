#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QPainter>

#include <iostream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_previousSliderValue(100),
    m_ActiveFileName("")
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

void MainWindow::DisplayImage(const QString &filename)
{
    QImageReader imagereader(filename);
    m_InputImagePixMap.load(filename);
    ui->imageLabel->setPixmap(m_InputImagePixMap.scaled(ui->imageLabel->width(),
                                                        ui->imageLabel->height(),
                                                        Qt::KeepAspectRatio));
    ui->imageLabel->setAlignment(Qt::AlignCenter);
    ui->horizontalSlider->show();
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    ui->imageLabel->setPixmap(m_InputImagePixMap.scaled(ui->imageLabel->width(),
                                                        ui->imageLabel->height(),
                                                        Qt::KeepAspectRatio));

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    std::cout << e->x() << " " << e->y() << std::endl;
    auto inputImageRect = m_InputImagePixMap.rect();
    inputImageRect.translate(e->pos());
    update();

}

void MainWindow::Open()
{
    m_ActiveFileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "C:/", tr("Image Files (*.png *.jpg *.bmp)"));
    DisplayImage(m_ActiveFileName);
}

void MainWindow::SaveFileCopy()
{
    QFile currentFile(m_ActiveFileName);
    QFileInfo fileInfo(currentFile.fileName());
    QString filename(fileInfo.fileName());
    std::cout << filename.toStdString() << std::endl;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    float zoomFactor = static_cast<float>(value) / m_previousSliderValue;
    ui->imageLabel->setPixmap(m_InputImagePixMap.scaled(static_cast<int>(ui->imageLabel->width() * zoomFactor),
                                                        static_cast<int>(ui->imageLabel->height() * zoomFactor),
                                                        Qt::KeepAspectRatio));
}
