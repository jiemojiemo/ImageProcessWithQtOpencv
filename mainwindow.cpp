#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "core.hpp"
#include "imgproc.hpp"

#include "Magic/EdgeDetector.h"
#include "Magic/GrayScaler.h"
#include "Magic/OilPainter.h"
#include "Magic/MagicianFactory.h"
#include "FileOperator/QImageFileOperator.h"
#include "Context/Context.h"
#include "iconwidget.h"

#include "batchwindow.hpp"

#include <memory>

#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QMatrix>
#include <QGridLayout>

#define GET_CLASS_DO_MAGIC_THEN_SHOW(className)			\
auto magician(MagicianFactory::SharedMagicianFactory().GetMagicianByName(className));\
if (magician != nullptr)\
{\
	m_img.SetMag(magician);\
	m_img.DoMagic();\
	ShowImage(m_img);\
}

#define GET_CLASS_STR_NAME Context::GetContext().GetMagicanNameFromFunctionName(__FUNCTION__)

#define DO_PROCESS_AND_SHOW GET_CLASS_DO_MAGIC_THEN_SHOW(GET_CLASS_STR_NAME)


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	Context::GetContext();
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
	//m_img = QImage(filename);

}

void MainWindow::ShowImageInGraphicsView(const QImage &qImg)
{
	ui->graphicsView->resize(qImg.width(), qImg.height());

	auto graphicsScenc = new QGraphicsScene();
	graphicsScenc->addPixmap(QPixmap::fromImage(qImg));

	ui->graphicsView->setScene(graphicsScenc);
	ui->graphicsView->adjustSize();
	ui->graphicsView->show();
}


void MainWindow::ShowImageInGraphicsView(const MImage& img)
{
	ShowImageInGraphicsView(img.GetQImage());
}



void MainWindow::ShowImage(const MImage& img)
{
	ShowImageInGraphicsView(img);
}

void MainWindow::on_actionOpen_triggered()
{
	std::unique_ptr<ImageFileOperator> fileOperator(std::make_unique<QImageFileOperator>());
	auto filename = fileOperator->Open();
	if (!filename.empty())
	{
		Context::GetContext().SetCurrentFilename(QString::fromStdString(filename));
		ReadImage(Context::GetContext().GetCurrentFilename());
		ShowImage(m_img);
	}
}

void MainWindow::on_actionClose_triggered()
{
    ui->graphicsView->scene()->clear();
}

void MainWindow::on_actionSave_triggered()
{
	std::unique_ptr<ImageFileOperator> fileOperator(std::make_unique<QImageFileOperator>());
	fileOperator->Save(m_img, Context::GetContext().GetCurrentFilename().toStdString());
}

void MainWindow::on_actionSave_As_triggered()
{
	auto fileOperator(std::make_unique<QImageFileOperator>());
	fileOperator->SaveAs(m_img);
}

void MainWindow::on_actionBatching_triggered()
{
	BatchWindow* batchWin = new BatchWindow(this);
	//batchWin->setWindowModality(Qt::ApplicationModal);

	batchWin->show();
	//this->hide();
	//this->close();
}

void MainWindow::on_actionLeft_90_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void MainWindow::on_actionRight_90_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void MainWindow::on_actionEdge_Detect_triggered()
{
	DO_PROCESS_AND_SHOW;

}

void MainWindow::on_actionGray_Scale_triggered()
{
	//GET_CLASS_DO_MAGIC(GrayScaler);
	DO_PROCESS_AND_SHOW;

}

void MainWindow::on_actionOil_triggered()
{
	//GET_CLASS_DO_MAGIC(OilPainter);
	DO_PROCESS_AND_SHOW;
}

void MainWindow::on_actionContour_triggered()
{
	DO_PROCESS_AND_SHOW;
}

