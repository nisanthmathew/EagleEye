#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <../Singletons/logger.h>
#include <../Singletons/imageviewcontroller.h>
#include <../Utilities/displayformatutilities.h>
#include <../Utilities/imagereadwriteutilities.h>

#include <QObject>
#include <QStandardItemModel>
#include <QWheelEvent>

namespace EagleEye {
class ImageModel : public QStandardItemModel
{
    Q_OBJECT

    friend class ImageViewController;

public:
    explicit ImageModel(QObject *parent = nullptr);

    enum ImageModelIndex : int
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

    // setter and getter for data using ImageModelIndex
    template <typename T>
    bool SetData(ImageModelIndex imageModelIndex, const T &data)
    {
      auto dataIndex = index(imageModelIndex, 0);
      return QStandardItemModel::setData(dataIndex, QVariant::fromValue(data));
    }

    template <typename T>
    T GetData(const ImageModelIndex modelIndex) const
    {
      const QVariant &variant = data(index(modelIndex, 0));
      T value;
      if (variant.isValid() && !variant.isNull())
      {
        value = variant.value<T>();
      }
      return value;
    }

    virtual QModelIndex	index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;
    void TriggerDataChange(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private:
    void SetNewImage();
    void SaveDisplayedImage();
    void SetZoomFactor(QWheelEvent *e);
    void ResizeImageLabel(const QSize &size);
    void ConvertDisplayFormat(EagleEye::DisplayFormats displayFormat);
    void SelectRectangularRegionOfInterest(bool start);

    //member variables these are not set in the model as there is no need in notifying obeservers about them.
    std::unique_ptr<EagleEye::ImageReadWrite> m_ImageReadWrite;

};
}

#endif // IMAGEMODEL_H
