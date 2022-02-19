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
    QCOMPARE(ImageWriter.SaveImageCopy(imageToSave), false);
    ImageWriter.LoadImage();

    QImageReader imageReader(EagleEye::DataHandler::DATA_HANDLER().GetActiveFilePath());
    QPixmap newPixMap = QPixmap::fromImageReader(&imageReader);
    bool success = ImageWriter.SaveImageCopy(newPixMap);
    QCOMPARE(success, true);
}

QTEST_MAIN(ToolsTest)

#include "ToolsTest.moc"
