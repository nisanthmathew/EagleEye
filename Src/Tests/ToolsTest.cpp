#include <QTest>
#include <QObject>
#include <QImageReader>
#include <imagereadwrite.h>
#include <displayformat.h>
#include <../datahandler.h>
class ToolsTest : public QObject
{
    Q_OBJECT

public:
    ToolsTest();
    ~ToolsTest();

private slots:
    void TestSaveFileCopy();

};


ToolsTest::ToolsTest()
{

}

ToolsTest::~ToolsTest()
{

}


void ToolsTest::TestSaveFileCopy()
{
    EagleEye::ImageReadWrite ImageWriter;
    QPixmap imageToSave;
    QCOMPARE(ImageWriter.EESaveImageCopy(imageToSave), false);
    ImageWriter.EELoadImage();

    QImageReader imageReader(EagleEye::DataHandler::SINGLE_INSTANCE().GetActiveFilePath());
    QPixmap newPixMap = QPixmap::fromImageReader(&imageReader);
    bool success = ImageWriter.EESaveImageCopy(newPixMap);
    QCOMPARE(success, true);
}

QTEST_MAIN(ToolsTest)

#include "ToolsTest.moc"
