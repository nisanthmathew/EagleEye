#include <QTest>
#include <QObject>
#include <QImageReader>
#include <../Utilities/imagereadwriteutilities.h>
#include <../Utilities/displayformatutilities.h>
#include <../Singletons/data.h>
class ImageReadWriteTest : public QObject
{
    Q_OBJECT

public:
    ImageReadWriteTest();
    ~ImageReadWriteTest();

private slots:
    void TestSaveFileCopy();

};


ImageReadWriteTest::ImageReadWriteTest()
{

}

ImageReadWriteTest::~ImageReadWriteTest()
{

}


void ImageReadWriteTest::TestSaveFileCopy()
{
    EagleEye::ImageReadWrite ImageWriter;
    QPixmap imageToSave;
    QCOMPARE(ImageWriter.EESaveImageCopy(imageToSave), false);

    QString filePath {QCoreApplication::applicationDirPath() + "/TestImage.png"};
    ImageWriter.EELoadImage(filePath);

    QImageReader imageReader(filePath);
    QPixmap newPixMap = QPixmap::fromImageReader(&imageReader);
    bool success = ImageWriter.EESaveImageCopy(newPixMap, QCoreApplication::applicationDirPath() + "/TestImage.png");
    QCOMPARE(success, true);
}

QTEST_MAIN(ImageReadWriteTest)

#include "imagereadwriteutilitiestest.moc"
