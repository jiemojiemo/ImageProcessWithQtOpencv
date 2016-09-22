#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "core.hpp"
#include "imgproc.hpp"

#include "Magic/EdgeDetector.h"
#include "Magic/GrayScaler.h"
#include "ImageChanger/ImageToQImage.h"
#include "FileOperator/ImageFileOperator.h"
#include "FileOperator/QImageFileOperator.h"
#include "ImageRotator/QImageRotator.h"
#include "Context/Context.h"

#include <memory>

#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QMatrix>

void DoRotate(QImage& qImg, int rotate)
{
	QMatrix rotateMatrix;
	rotateMatrix.rotate(rotate);
	qImg = qImg.transformed(rotateMatrix);
}

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

	m_qtImg = ImageToQImage::DoChange(m_img);
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

void MainWindow::ShowImageInGraphicsView(const QImage &qImg)
{
    ui->graphicsView->resize(qImg.width(), qImg.height());

    auto graphicsScenc = new QGraphicsScene();
    graphicsScenc->addPixmap(QPixmap::fromImage(qImg));

    ui->graphicsView->setScene(graphicsScenc);
    ui->graphicsView->adjustSize();
    ui->label->hide();
    ui->graphicsView->show();
}


void MainWindow::ShowImageInGraphicsView(const Image& img)
{
	m_qtImg = ImageToQImage::DoChange(img);
	ShowImageInGraphicsView(m_qtImg);
}

void MainWindow::ShowImageInGraphicsView()
{
	ShowImageInGraphicsView(m_img);
}

void MainWindow::on_actionOpen_triggered()
{
	auto fileOperator(std::make_unique<QImageFileOperator>());
	Context::GetContext().SetCurrentFilename( QString::fromStdString(fileOperator->Open()));
    ReadImage(Context::GetContext().GetCurrentFilename());
    ShowImage();
}

void MainWindow::on_actionEdge_Detect_triggered()
{
	EdgeDetector edge;
	edge.DoMagic(m_img);
    ShowImageInGraphicsView();
}

void MainWindow::on_actionClose_triggered()
{
    ui->graphicsView->scene()->clear();
}

void MainWindow::on_actionSave_triggered()
{
	auto fileOperator(std::make_unique<QImageFileOperator>());
	fileOperator->Save(m_img, Context::GetContext().GetCurrentFilename().toStdString());
}

void MainWindow::on_actionSave_As_triggered()
{
	auto fileOperator(std::make_unique<QImageFileOperator>());
	fileOperator->SaveAs(m_img);
}

void MainWindow::on_actionLeft_90_triggered()
{
	QImageRotator rotate;
	rotate.Rotate(m_qtImg,Context::CtxLeftRotateDegree);
	ShowImageInGraphicsView();
}

void MainWindow::on_actionRight_90_triggered()
{
	QImageRotator rotate;
	rotate.Rotate(m_qtImg, Context::CtxRightRotateDegree);
	ShowImageInGraphicsView();
}

void MainWindow::on_actionGray_Scale_triggered()
{
	GrayScaler grayScaler;
	grayScaler.DoMagic(m_img);
	ShowImageInGraphicsView();
}

