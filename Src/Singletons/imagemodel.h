#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <../Utilities/imagereadwriteutilities.h>

#include <QObject>
#include <QStandardItemModel>
#include <QWheelEvent>

namespace EagleEye {

class Logger;
class ImageViewController;
enum class DisplayFormats;

enum class ImageModelIndex : int
{
    OriginalImagePixmap = 0,
    DisplayedImagePixmap,
    ImageLabelPixmap,
    ROIPixmap,
    RectangularROI,
    ActiveImagePath,
    ZoomFactor,
    SelectRectangularROI,
    ImageViewLabelWidth,
    ImageViewLabelHeight,

    RowCount //last item to keep count of rows
};

class ImageModel : public QStandardItemModel
{
    Q_OBJECT

    friend class ImageViewController;

public:
    explicit ImageModel(QObject *parent = nullptr);

    // setter and getter for data using ImageModelIndex
    template <typename T>
    bool SetData(ImageModelIndex imageModelIndex, const T &data)
    {
      auto dataIndex = index(static_cast<int>(imageModelIndex), 0);
      return QStandardItemModel::setData(dataIndex, QVariant::fromValue(data));
    }

    template <typename T>
    T GetData(const ImageModelIndex modelIndex) const
    {
      const QVariant &variant = data(index(static_cast<int>(modelIndex), 0));
      T value;
      if (variant.isValid() && !variant.isNull())
      {
        value = variant.value<T>();
      }
      return value;
    }

    QModelIndex	GetIndex(const ImageModelIndex row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
    void TriggerDataChange(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private:
    void SetNewImage();
    void SaveDisplayedImage();
    void SetZoomFactor(QWheelEvent *e);
    void ResizeImageLabel(const QSize &size);
    void ConvertDisplayFormat(const EagleEye::DisplayFormats displayFormat);
    void SelectRectangularRegionOfInterest(bool start);
    void SetRectangularROI(const QRect &ROI);
    void ClearRectangularROI();

    //member variables these are not set in the model as there is no need in notifying obeservers about them.
    std::unique_ptr<EagleEye::ImageReadWrite> m_ImageReadWrite;

};
}

#endif // IMAGEMODEL_H
