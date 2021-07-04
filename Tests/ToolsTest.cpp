#include <QTest>
#include <QObject>
#include <imagereadwrite.h>
class ToolsTest : public QObject
{
    Q_OBJECT

public:
    ToolsTest();
    ~ToolsTest();

private slots:
    void SaveFileCopy();

};


ToolsTest::ToolsTest()
{

}

ToolsTest::~ToolsTest()
{

}


void ToolsTest::SaveFileCopy()
{
    EagleEye::ImageReadWrite ImageWriter;
    QPixmap imageToSave;
    QCOMPARE(ImageWriter.SaveImageCopy(imageToSave), false);
}


QTEST_MAIN(ToolsTest)

#include "ToolsTest.moc"
