#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QAction>
#include <QPainter>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_previousSliderValue(100)
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
    connect(openAct,SIGNAL(triggered()),this,SLOT(open()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisplayImage(const QString filename)
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
    ui->imageLabel->setPixmap(m_InputImagePixMap.scaled(ui->imageLabel->width(),
                                                      ui->imageLabel->height(),
                                                        Qt::KeepAspectRatio));
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QPainter panPainter;
    panPainter.drawImage(e->pos(),m_InputImagePixMap.toImage());
    std::cout << e->x() << " " << e->y() << std::endl;

}

void MainWindow::open()
{
    QString m_FileName = QFileDialog::getOpenFileName(this,
                 tr("Open Image"), "C:/", tr("Image Files (*.png *.jpg *.bmp)"));
    DisplayImage(m_FileName);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    float zoomFactor = static_cast<float>(value) / m_previousSliderValue;
    ui->imageLabel->setPixmap(m_InputImagePixMap.scaled(static_cast<int>(ui->imageLabel->width() * zoomFactor),
                                                        static_cast<int>(ui->imageLabel->height() * zoomFactor),
                                                        Qt::KeepAspectRatio));
}
