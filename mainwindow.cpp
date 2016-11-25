#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "core.hpp"
#include "imgproc.hpp"

#include "Magic/EdgeDetector.h"
#include "Magic/GrayScaler.h"
#include "Magic/OilPainter.h"
#include "Magic/MagicianFactory.h"
#include "Magic/HorizontalTextPainterImpl.h"
#include "FileOperator/QImageFileOperator.h"
#include "Context/Context.h"
#include "iconwidget.h"

#include "batchwindow.hpp"
#include "ImageDatabaseWindow.h"
#include "InputTextDialog.h"
#include "SaveImageDialog.h"

#include <memory>

#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QMatrix>
#include <QGridLayout>
#include <QTextEdit>

#include <windows.h>

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
    ui(new Ui::MainWindow),
	m_layout(new QGridLayout(this)),
	m_graphicsScene(new QGraphicsScene(this)),
	m_batchWin(nullptr),
	m_databaseWin(nullptr),
	m_textWin(nullptr)
{
    ui->setupUi(this);

	InitUi();
	Context::GetContext();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::GetText()
{
	if (m_textWin == nullptr)
	{
		m_textWin = new InputTextDialog(this);

	}
	if (m_textWin->exec() == QDialog::Accepted)
	{
		return m_textWin->GetTextEditString();
	}
	else
	{
		return QString();
	}
	
}

QString MainWindow::GetFilename()
{
    QString filename = QFileDialog::getOpenFileName(
                this,tr("Open Image"),".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
	return filename;
}

void MainWindow::PaintTextOnImage(const QString& text)
{
	QTextPainter* painter = new HorizontalTextPainterImpl();
	ON_SCOPE_EXIT([&painter]() {delete painter; });

	m_img = painter->PaintText(m_img, text.toStdString());


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
	int imgWidth = qImg.width();
	int imgHeight = qImg.height();

	AdjustSize(imgWidth, imgHeight);

	if (m_graphicsScene != nullptr)
	{
		delete m_graphicsScene;
		m_graphicsScene = new QGraphicsScene(this);
		m_graphicsScene->addPixmap(QPixmap::fromImage(qImg));
		ui->graphicsView->setScene(m_graphicsScene);
	}
	ui->graphicsView->adjustSize();
	SetLayout();

}


void MainWindow::ShowImageInGraphicsView(const MImage& img)
{
	ShowImageInGraphicsView(img.GetQImage());
}



void MainWindow::ShowImage(const MImage& img)
{
	ShowImageInGraphicsView(img);
}

void MainWindow::InitUi()
{
	AdjustSize();
	SetLayout();
	ui->graphicsView->setScene(m_graphicsScene);
	ui->graphicsView->show();

	SetNoImageState();
}

void MainWindow::AdjustSize(int newW/*=700*/, int newH/*=600*/)
{
	int w = newW < kMinWinWidth ? kMinWinWidth : newW;
	int h = newH < kMinWinHeight ? kMinWinHeight : newH;

	this->resize(w,h);
}

void MainWindow::SetLayout()
{
	m_layout->addWidget(ui->graphicsView, 0, Qt::AlignCenter);
	ui->centralWidget->setLayout(m_layout);
}

void MainWindow::SetNewImageState()
{
	this->raise();
	SetProcessDisabled(false);
	SetFileActionsDisable(false);
	SetRotateDisabled(false);
	SetAddTextDisable(false);
}

void MainWindow::SetNoImageState()
{
	SetProcessDisabled(true);
	SetFileActionsDisable(true);
	SetRotateDisabled(true);
	SetAddTextDisable(true);
}

void MainWindow::SetFileActionsDisable(bool b/*=false*/)
{
	ui->actionClose->setDisabled(b);
	ui->actionSave->setDisabled(b);
	ui->actionSave_As->setDisabled(b);
	ui->actionShare_To_Weibo->setDisabled(b);
}

void MainWindow::SetProcessDisabled(bool b)
{
	ui->menuProcess->setDisabled(b);
}

void MainWindow::SetRotateDisabled(bool b /*= false*/)
{
	ui->menuRotate->setDisabled(b);
}

void MainWindow::SetAddTextDisable(bool b /*= false*/)
{
	ui->menuAddText->setDisabled(b);
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
		SetNewImageState();
	}

}

void MainWindow::on_actionClose_triggered()
{
    ui->graphicsView->scene()->clear();
	Context::GetContext().SetCurrentFilename("");
	SetNoImageState();
}

void MainWindow::on_actionSave_triggered()
{
	if (Context::GetContext().GetCurrentFilename() == "")
	{
		on_actionSave_As_triggered();
	}
	else
	{
		SaveImageDialog dialog;
		if (dialog.exec() == QDialog::Accepted)
		{
			std::unique_ptr<ImageFileOperator> fileOperator(std::make_unique<QImageFileOperator>());
			fileOperator->Save(m_img, Context::GetContext().GetCurrentFilename().toStdString());
		}
	}
}

void MainWindow::on_actionSave_As_triggered()
{
	auto fileOperator(std::make_unique<QImageFileOperator>());
	auto newFilename = fileOperator->SaveAs(m_img);
	if (!newFilename.empty())
	{
		Context::GetContext().SetCurrentFilename(QString::fromStdString(newFilename));
	}
}

void MainWindow::on_actionBatching_triggered()
{
	if (m_batchWin == nullptr)
	{
		m_batchWin = new BatchWindow(this);
	}
	m_batchWin->show();
	//BatchWindow* batchWin = new BatchWindow(this);

	//batchWin->show();
	//static BatchWindow batchWin(this);
	//batchWin.show();
}

void MainWindow::on_actionImage_Database_triggered()
{
	if (m_databaseWin == nullptr)
	{
		m_databaseWin = new ImageDatabaseWindow("images.db", "images_tab", this);
	}
	m_databaseWin->show();

}

void MainWindow::on_actionShare_To_Weibo_triggered()
{
	auto fileOperator(std::make_unique<QImageFileOperator>());

	auto filepath = Context::GetContext().GetCurrentFilename();
	auto a = filepath.toStdString();
	std::string execLine = "G:\\C++\\HelloOpencvInQt\\dist\\testFuck.exe By-magic ";
	execLine += a;
	WinExec(execLine.c_str(), SW_HIDE);
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

void MainWindow::on_actionStrech_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void MainWindow::on_actionEmboss_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void MainWindow::on_actionCarve_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void MainWindow::on_actionHorizontal_Text_triggered()
{
	DO_PROCESS_AND_SHOW;
	auto text = GetText();
	PaintTextOnImage(text);
	ShowImage(m_img);
}

//void MainWindow::on_actionVertical_Text_triggered()
//{
//	DO_PROCESS_AND_SHOW;
//	auto text = GetText();
//	PaintTextOnImage(text);
//	ShowImage(m_img);
//}

void MainWindow::on_actionUndo_triggered()
{
	m_img.Undo();
	ShowImage(m_img);
}

void MainWindow::ReceiveImage(cv::Mat& mat)
{
	Context::GetContext().SetCurrentFilename("");
	m_img = mat;
	SetNewImageState();
	ShowImage(m_img);
}

void MainWindow::ReceiveImage(QImage& img)
{
	Context::GetContext().SetCurrentFilename("");
	m_img = img;
	SetNewImageState();
	ShowImage(m_img);
}

