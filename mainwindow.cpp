#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "core.hpp"
#include "imgproc.hpp"


#include <QString>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ID_BUT_READ_clicked()
{
    auto filename = GetFilename();
    ReadImage(filename);
    ShowImage();
}

void MainWindow::on_ID_BUT_PROC_clicked()
{
    cv::Mat dst;

           //输入图像
           //输出图像
           //输入图像颜色通道数
           //x方向阶数
           //y方向阶数
    cv::Sobel(m_img,dst,m_img.depth(),1,1);
    CVMatToQImage(dst, m_qtImg);
    ShowImageInGraphicsView(m_qtImg);
}

QString MainWindow::GetFilename()
{
    QString filename = QFileDialog::getOpenFileName(
                this,tr("Open Image"),".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
    return filename;
}

void MainWindow::ReadImage(const QString& filename)
{
    QByteArray ba = filename.toLocal8Bit();
    m_img = cv::imread(ba.data());


    cv::cvtColor(m_img,m_img, CV_BGR2RGB);
    CVMatToQImage(m_img, m_qtImg);
    //QImage img =  QImage((const unsigned char*)(m_img.data),m_img.cols,m_img.rows,m_img.cols*m_img.channels(),QImage::Format_RGB888);
    //QImage img =  QImage((const unsigned char*)(matTmp.data),matTmp.cols,matTmp.rows,matTmp.cols*matTmp.channels(),QImage::Format_RGB888);
    //m_qtImg = img;
}

void MainWindow::CVMatToQImage(const cv::Mat &mat, QImage &img)
{
    img =  QImage((const unsigned char*)(mat.data),mat.cols,mat.rows,mat.cols*mat.channels(),QImage::Format_RGB888);
}

void MainWindow::ShowImage()
{

    //ShowImageInLabel(m_qtImg);
    ShowImageInGraphicsView(m_qtImg);
}

void MainWindow::ShowImageInLabel(const QImage &img)
{
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());

    ui->label->show();
    ui->graphicsView->hide();
}

void MainWindow::ShowImageInGraphicsView(const QImage &img)
{
    ui->graphicsView->resize(img.width(), img.height());
    auto graphicsScenc = new QGraphicsScene();
    graphicsScenc->addPixmap(QPixmap::fromImage(img));

    ui->graphicsView->setScene(graphicsScenc);
    ui->graphicsView->adjustSize();
    ui->label->hide();
    ui->graphicsView->show();
}

