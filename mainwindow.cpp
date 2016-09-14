#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "core.hpp"
#include "imgproc.hpp"

#include "Magic/EdgeDetector.h"

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

QString MainWindow::GetFilename()
{
    QString filename = QFileDialog::getOpenFileName(
                this,tr("Open Image"),".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
	return filename;
}

void MainWindow::ReadImage(const QString& filename)
{
	if (filename.isEmpty())
		return;

    QByteArray ba = filename.toLocal8Bit();
	m_img = cv::imread(ba.data());

    //cv::cvtColor(m_img.GetMat(),m_img.GetMat(), CV_BGR2RGB);
    CVMatToQImage(m_img, m_qtImg);
}

void MainWindow::CVMatToQImage(const cv::Mat &mat, QImage &img)
{
    img =  QImage((const unsigned char*)(mat.data),mat.cols,mat.rows,mat.cols*mat.channels(),QImage::Format_RGB888);
}
void MainWindow::CVMatToQImage(const Image& img, QImage& qImg)
{
	this->CVMatToQImage(img.GetMat(), qImg);
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


void MainWindow::on_actionOpen_triggered()
{
    auto filename = GetFilename();
    ReadImage(filename);
    ShowImage();
}

void MainWindow::on_actionEdge_Detect_triggered()
{
	EdgeDetector edge;
	edge.DoMagic(m_img);
	CVMatToQImage(m_img, m_qtImg);
    ShowImageInGraphicsView(m_qtImg);
}

void MainWindow::on_actionClose_triggered()
{
    ui->graphicsView->scene()->clear();

}
