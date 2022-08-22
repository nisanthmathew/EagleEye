#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QDate>
#include <QRubberBand>
#include <QItemSelectionRange>

#include <iostream>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(1, 1);
    setWindowTitle("EagleEye");

    ui->imageLabel->setAlignment(Qt::AlignCenter);
    m_RectangularSelectedRegion = std::unique_ptr<EagleEye::EEROIQRubberBand>(new EagleEye::EEROIQRubberBand(QRubberBand::Rectangle, ui->imageLabel));
    m_RectangularSelectedRegion->setObjectName("EERectangularSelectedRegion");
    m_ImageModel = new EagleEye::ImageModel(this);
    connect(m_ImageModel, &EagleEye::ImageModel::dataChanged, this, &MainWindow::OnImageModelDataChanged);

    m_ImageViewController = new EagleEye::ImageViewController(this, m_ImageModel);
    this->installEventFilter(m_ImageViewController);

    m_FileMenu = new EagleEye::EEFileMenu(menuBar()->addMenu("&File"), m_ImageViewController);
    m_ToolsMenu = new EagleEye::EEToolsMenu(menuBar()->addMenu("&Tools"), m_ImageViewController);
    m_ImageProcessingMenu = new EagleEye::EEImageProcessingMenu(menuBar()->addMenu("&Image Processing"), m_ImageViewController);
}

MainWindow::~MainWindow()
{
    delete m_FileMenu;
    delete m_ToolsMenu;
    delete m_ImageProcessingMenu;
    delete ui;
}

void MainWindow::OnImageModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    const auto range = QItemSelectionRange(topLeft, bottomRight);
    if (range.contains(m_ImageModel->index(EagleEye::ImageModel::ImageLabelPixmap)))
    {
        ui->imageLabel->setPixmap(m_ImageModel->GetData<QPixmap>(EagleEye::ImageModel::ImageLabelPixmap));
    }

    if (range.contains(m_ImageModel->index(EagleEye::ImageModel::SelectRectangularROI)) ||
            range.contains(m_ImageModel->index(EagleEye::ImageModel::ImageLabelPixmap)))
    {
        m_RectangularSelectedRegion->hide(); // clear as already set ROI is not valid anymore
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    m_MouseStartPoint = ui->imageLabel->mapFrom(this, e->pos());
    if (m_ImageModel->GetData<bool>(EagleEye::ImageModel::SelectRectangularROI))
    {
        m_RectangularSelectedRegion->setGeometry(QRect(m_MouseStartPoint, QSize(0,0)));
        m_RectangularSelectedRegion->show();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (m_ImageModel->GetData<bool>(EagleEye::ImageModel::SelectRectangularROI))
    {
        m_RectangularSelectedRegion->setGeometry(QRect(m_MouseStartPoint, ui->imageLabel->mapFrom(this, e->pos())).normalized());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (m_ImageModel->GetData<bool>(EagleEye::ImageModel::SelectRectangularROI))
    {
        const auto rubberbandGeometry = m_RectangularSelectedRegion->geometry();
        if (rubberbandGeometry.width() == 0 || rubberbandGeometry.height() == 0)
            return;

        QPixmap displayedPixmap = m_ImageModel->GetData<QPixmap>(EagleEye::ImageModel::ImageLabelPixmap);
        const auto topLeft = MapPointToPixmap(rubberbandGeometry.topLeft(), &displayedPixmap);
        const auto bottomRight = MapPointToPixmap(rubberbandGeometry.bottomRight(), &displayedPixmap);
        QRect ROI (topLeft, bottomRight);
        m_ImageViewController->SetRectangularROI(ROI);
    }
}

QPoint MainWindow::MapPointToPixmap(QPoint point, QPixmap *pixmap)
{
    auto mappedPoint = ui->imageLabel->mapFrom(this, point);
    mappedPoint.setX(point.x() - int((ui->imageLabel->width() - pixmap->width()) / 2));
    mappedPoint.setY(point.y() - int((ui->imageLabel->height() - pixmap->height()) / 2));
    return mappedPoint;
}
