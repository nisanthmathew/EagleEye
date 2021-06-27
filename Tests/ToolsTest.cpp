#include <QTest>
#include <QObject>
#include <filereadwrite.h>
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
    FileReadWrite ImageWriter;
    bool success {ImageWriter.SaveImageCopy()};
    QCOMPARE(success, true);
}


QTEST_MAIN(ToolsTest)

#include "ToolsTest.moc"
