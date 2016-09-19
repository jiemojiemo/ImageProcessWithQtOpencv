#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "core.hpp"
#include "imgproc.hpp"

#include "Magic/EdgeDetector.h"
#include "ImageChanger/ToQImage.h"
#include "FileOperator/ImageFileOperator.h"
#include "FileOperator/QImageFileOperator.h"

#include <memory>

#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

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
	ToQImage::DoChange(m_img, m_qtImg);
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
	auto fileOperator(std::make_unique<QImageFileOperator>());

	m_openedFilename = QString::fromStdString(fileOperator->Open());
    ReadImage(m_openedFilename);
    ShowImage();
}

void MainWindow::on_actionEdge_Detect_triggered()
{
	EdgeDetector edge;
	edge.DoMagic(m_img);
	ToQImage::DoChange(m_img, m_qtImg);
    ShowImageInGraphicsView(m_qtImg);
}

void MainWindow::on_actionClose_triggered()
{
    ui->graphicsView->scene()->clear();
}

void MainWindow::on_actionSave_triggered()
{
	auto fileOperator(std::make_unique<QImageFileOperator>());
	fileOperator->Save(m_img, m_openedFilename.toStdString());
}

void MainWindow::on_actionSave_As_triggered()
{
	auto fileOperator(std::make_unique<QImageFileOperator>());
	fileOperator->SaveAs(m_img);
}

