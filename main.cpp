#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

#pragma comment(lib, "./opencv/x64/vc14/lib/opencv_world310.lib")
#pragma comment(lib, "./opencv/x64/vc14/lib/opencv_world310d.lib")

void ShowImageTest();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

    w.show();

    return a.exec();
}

void ShowImageTest()
{
    //声明IplImage指针
    IplImage *pImg;
    //载入图片
    pImg = cvLoadImage("G:\\C++\\HelloOpencvInQt\\1.JPG", 1);
    //创建窗口
    cvNamedWindow("Image",1);
    //显示图像
    cvShowImage("Image",pImg);
    //等待按键
    cvWaitKey(0);
    //销毁窗口
    cvDestroyWindow("Image");
    //释放图像
    cvReleaseImage(&pImg);
}
