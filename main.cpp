#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

#pragma comment(lib, "./opencv/x64/vc14/lib/opencv_world310.lib")
#pragma comment(lib, "./opencv/x64/vc14/lib/opencv_world310d.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

    w.show();

    return a.exec();
}
