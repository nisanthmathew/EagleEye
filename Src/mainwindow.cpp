#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eeroiqrubberband.h"

#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QDate>
#include <QRubberBand>
#include <QItemSelectionRange>

#include <iostream>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Rubberband(nullptr)
{
    ui->setupUi(this);
    setMinimumSize(1, 1);
    setWindowTitle("EagleEye");

    ui->imageLabel->setAlignment(Qt::AlignCenter);

    m_ImageModel = new EagleEye::ImageModel(this);
    connect(m_ImageModel, &EagleEye::ImageModel::dataChanged, this, &MainWindow::OnImageModelDataChanged);

    m_ImageViewController = new EagleEye::ImageViewController(this, m_ImageModel);
    this->installEventFilter(m_ImageViewController);


    m_FileMenu = new EagleEye::EEFileMenu(menuBar()->addMenu("&File"), m_ImageViewController);
    m_ToolsMenu = new EagleEye::EEToolsMenu(menuBar()->addMenu("&Tools"));
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
        auto pixmap = m_ImageModel->GetData<QPixmap>(EagleEye::ImageModel::ImageLabelPixmap);
        ui->imageLabel->setPixmap(pixmap);
    }

    if (range.contains(m_ImageModel->index(EagleEye::ImageModel::DisplayedImagePixmap)))
    {
        EagleEye::Logger::CENTRAL_LOGGER().LogMessage("MainWindow::OnImageModelDataChanged(): DisplayedImagePixmap changed.",
                                                      EagleEye::LOGLEVEL::EE_DEBUG);
        auto pixmap {m_ImageModel->GetData<QPixmap>(EagleEye::ImageModel::DisplayedImagePixmap)};
        auto zoomFactor {m_ImageModel->GetData<float>(EagleEye::ImageModel::ZoomFactor)};
        ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->width() * zoomFactor, ui->imageLabel->height() * zoomFactor,
                                                    Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    m_MouseStartPoint = ui->imageLabel->mapFrom(this, e->pos());
    if (EagleEye::Data::SINGLE_INSTANCE().GetSelectROI())
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
    if (EagleEye::Data::SINGLE_INSTANCE().GetSelectROI() && m_Rubberband)
    {
        m_Rubberband->setGeometry(QRect(m_MouseStartPoint, ui->imageLabel->mapFrom(this, e->pos())).normalized());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (EagleEye::Data::SINGLE_INSTANCE().GetSelectROI() && m_Rubberband)
    {
        const auto rubberbandGeometry = m_Rubberband->geometry();
        if (rubberbandGeometry.width() == 0 || rubberbandGeometry.height() == 0)
            return;

        QPixmap displayedPixmap = ui->imageLabel->pixmap(Qt::ReturnByValue);
        const auto topLeft = MapPointToPixmap(rubberbandGeometry.topLeft(), &displayedPixmap);
        const auto bottomRight = MapPointToPixmap(rubberbandGeometry.bottomRight(), &displayedPixmap);
        QRect ROI (topLeft, bottomRight);
        EagleEye::Data::SINGLE_INSTANCE().SetRegionOfinterset(ROI);
        EagleEye::Data::SINGLE_INSTANCE().SetROIPixmap(displayedPixmap.copy(ROI));
    }
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
    if (m_Rubberband)
    {
        m_Rubberband->hide();
        EagleEye::Data::SINGLE_INSTANCE().SetROIPixmap(QPixmap());
        EagleEye::Data::SINGLE_INSTANCE().SetRegionOfinterset(QRect());
    }
}

QPoint MainWindow::MapPointToPixmap(QPoint point, QPixmap *pixmap)
{
    auto mappedPoint = ui->imageLabel->mapFrom(this, point);
    mappedPoint.setX(point.x() - int((ui->imageLabel->width() - pixmap->width()) / 2));
    mappedPoint.setY(point.y() - int((ui->imageLabel->height() - pixmap->height()) / 2));
    return mappedPoint;
}
