#include "mainwindow.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon("H:\\EagleEyeSoftware\\g963.png"));
    w.showMaximized();
    return a.exec();
}
