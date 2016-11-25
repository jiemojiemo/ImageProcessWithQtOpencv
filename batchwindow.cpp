#include "batchwindow.hpp"
#include "iconwidget.h"
#include "ImageBox.h"
#include "SaveImageDialog.h"
#include "InputTextDialog.h"
#include "DataStructure/MImage.h"
#include "DataStructure/BufferImage.h"
#include "FileOperator/QImageBatchFileOperator.h"
#include "Context/Context.h"
#include "Magic/MagicianFactory.h"
#include "Magic/ImageMeger.h"
#include "Magic/HorizontalMerger.h"
#include "Magic/VerticalMerger.h"
#include "Magic/HorizontalTextPainterImpl.h"

#include <algorithm>


int kCount = 0;

#define GET_CLASS_DO_MAGIC_THEN_SHOW(className)			\
auto magician(MagicianFactory::SharedMagicianFactory().GetMagicianByName(className));\
for (auto &iter : m_iconList)\
{\
	iter->SetMag(magician);\
	iter->DoMagic();\
}

#define GET_CLASS_STR_NAME Context::GetContext().GetMagicanNameFromFunctionName(__FUNCTION__)

#define DO_PROCESS_AND_SHOW GET_CLASS_DO_MAGIC_THEN_SHOW(GET_CLASS_STR_NAME)

const int BatchWindow::kWinWidth = 700;
const int BatchWindow::kWinHeight = 600;

BatchWindow::BatchWindow(QWidget * parent) : QMainWindow(parent),
	m_textWin(nullptr)
{
	m_layout = new QGridLayout(this);
	m_containWidget = new QWidget(this);

	m_imgBox = new ImageBox();
	m_imgBox->setMode(ImageBox::AUTO_SIZE);
	m_imgBox->setWindowFlags(Qt::WindowStaysOnTopHint);

	ui.setupUi(this);
	this->resize(kWinWidth, kWinHeight);
	m_containWidget->setLayout(m_layout);
	ui.scrollArea->setWidgetResizable(true);
	ui.scrollArea->setWidget(m_containWidget);
	this->setCentralWidget(ui.scrollArea);

	SetNoImageState();

	connect(this, SIGNAL(SentMat(cv::Mat&)), parent, SLOT(ReceiveImage(cv::Mat&)));
}

BatchWindow::~BatchWindow() 
{
	if (m_imgBox != nullptr)
	{
		delete m_imgBox;
	}
}

void BatchWindow::on_actionOpen_New_Folder_triggered()
{
	QImageBatchFileOperator fileOperator;
	auto filePathList = fileOperator.OpenFolder();
	AddImage(filePathList);
	
}

void BatchWindow::on_actionOpen_New_Image_triggered()
{
	QImageBatchFileOperator fileOperator;
	auto filepath = fileOperator.Open();

	AddImage(filepath);

}

void BatchWindow::on_actionClear_All_triggered()
{
	//ui clear
	for (int i = 0; i < m_layout->count(); ++i)
	{
		auto item = m_layout->itemAt(i);
		m_layout->removeItem(item);
	}

	for (auto &iter : m_iconList)
	{
		iter->close();
		delete iter;
	}
	m_iconList.clear();

	SetNoImageState();
	
}

void BatchWindow::on_actionUndo_triggered()
{
	for (auto& item : m_iconList)
	{
		item->Undo();
	}
}

void BatchWindow::on_actionSave_triggered()
{
	SaveImageDialog dialog;
	if (dialog.exec() == QDialog::Accepted)
	{
		std::unique_ptr<ImageFileOperator> fileOperator(std::make_unique<QImageFileOperator>());
		for (auto& item : m_iconList)
		{
			fileOperator->Save(item->GetMImage(), Context::GetContext().GetCurrentFilename().toStdString());
		}
	}
}

void BatchWindow::on_actionSave_As_triggered()
{
	std::unique_ptr<ImageFileOperator> fileOperator(std::make_unique<QImageFileOperator>());
	for (auto& item : m_iconList)
	{
		fileOperator->Save(item->GetMImage(), GetNewNameForSaveAs(item->GetImagePath()).toStdString());
	}
}

void BatchWindow::on_actionVertical_Merge_triggered()
{
	ImageMerger* merge = new VerticalMerger;
	ON_SCOPE_EXIT([&merge]() {delete merge; });
	this->MergeImages(merge);
}

void BatchWindow::on_actionHorizontal_Merge_triggered()
{
	ImageMerger* merge = new HorizontalMerger;
	ON_SCOPE_EXIT([&merge]() {delete merge; });
	this->MergeImages(merge);
}

void BatchWindow::on_actionGray_Scale_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void BatchWindow::on_actionEdge_Detect_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void BatchWindow::on_actionOil_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void BatchWindow::on_actionEmboss_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void BatchWindow::on_actionCarve_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void BatchWindow::on_actionStrech_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void BatchWindow::on_actionLeft_90_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void BatchWindow::on_actionRight_90_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void BatchWindow::on_actionHorizontal_Text_triggered()
{
	DO_PROCESS_AND_SHOW;
	auto text = GetText();
	QTextPainter* painter = new HorizontalTextPainterImpl();
	ON_SCOPE_EXIT([&painter]() {delete painter; });

	for (auto& item : m_iconList)
	{
		item->SetQImage(painter->PaintText(item->GetMImage(), text.toStdString()));
	}
}

void BatchWindow::RemoveIcon(IconWidget* removeItem)
{
	m_iconList.remove(removeItem);
	m_layout->removeWidget(removeItem);
	delete removeItem;
}

void BatchWindow::ClickImage(IconWidget* item)
{
	m_imgBox->setImage(item->GetQImage());
	m_imgBox->show();
}

bool BatchWindow::IsExitFilePath(const std::string& imgPath)
{
	for (auto& iter : m_iconList)
	{
		if (iter->GetImagePath() == QString::fromStdString(imgPath))
			return true;
	}

	return false;
}

void BatchWindow::AddImage(const std::string& imgPath)
{
	if (!IsExitFilePath(imgPath))
	{
		if (m_iconList.empty())
		{
			SetNewImageState();
		}

		auto iconImg = new IconWidget(QString::fromStdString(imgPath), this);
		m_iconList.push_back(iconImg);
		m_layout->addWidget(iconImg, GetWidgetRowIndex(), GetWidgetColIndex());
	}
}

void BatchWindow::AddImage(const std::list<std::string>& imgPathList)
{
	for (auto &path : imgPathList)
	{
		AddImage(path);
	}
}

int BatchWindow::GetWidgetRowIndex()const
{
	int rowMaxCount = kWinWidth / IconWidget::kWindowWidth;
	int iconWidgetCount = m_iconList.size()-1;
	return iconWidgetCount / rowMaxCount;
}

int BatchWindow::GetWidgetColIndex()const
{
	int rowMaxCount = kWinWidth / IconWidget::kWindowWidth;
	int iconWidgetCount = m_iconList.size()-1;
	return iconWidgetCount % rowMaxCount;
}

void BatchWindow::MergeImages(ImageMerger* merge)
{
	for (auto& item : m_iconList)
	{
		merge->AddImage(item->GetMat());
	}
	auto result = merge->MergeImages();
	emit this->SentMat(result);
}

void BatchWindow::SetNewImageState()
{
	ui.actionSave->setDisabled(false);
	ui.actionSave_As->setDisabled(false);
	SetProcessDisable(false);
	SetRotateDisable(false);
	SetMergeDisable(false);
	SetAddTextDiable(false);
}

void BatchWindow::SetNoImageState()
{
	ui.actionSave->setDisabled(true);
	ui.actionSave_As->setDisabled(true);
	SetProcessDisable(true);
	SetRotateDisable(true);
	SetMergeDisable(true);
	SetAddTextDiable(true);
}

void BatchWindow::SetProcessDisable(bool b /*= true*/)
{
	ui.menuProcess->setDisabled(b);
}

void BatchWindow::SetRotateDisable(bool b /*= true*/)
{
	ui.menuRotate->setDisabled(b);
}

void BatchWindow::SetMergeDisable(bool b /*= true*/)
{
	ui.menuMerge->setDisabled(b);
}

void BatchWindow::SetAddTextDiable(bool b /*= true*/)
{
	ui.menuAddText->setDisabled(b);
}

QString BatchWindow::GetNewNameForSaveAs(const QString& name)const
{
	QStringList strList = name.split(".");
	QString newName = strList.at(0) + "_copy." + strList.at(1);
	return newName;
}

QString BatchWindow::GetText()
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
