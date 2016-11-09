#include "batchwindow.hpp"
#include "iconwidget.h"
#include "ImageBox.h"
#include "DataStructure/MImage.h"
#include "FileOperator/QImageBatchFileOperator.h"
#include "Context/Context.h"
#include "Magic/MagicianFactory.h"

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

BatchWindow::BatchWindow(QWidget * parent) : QMainWindow(parent) 
{
	m_layout = new QGridLayout(this);
	m_containWidget = new QWidget(this);

	m_imgBox = new ImageBox();
	m_imgBox->setMode(ImageBox::AUTO_SIZE);
	m_imgBox->setWindowFlags(Qt::WindowStaysOnTopHint);

	ui.setupUi(this);

	m_containWidget->setLayout(m_layout);
	ui.scrollArea->setWidgetResizable(true);
	ui.scrollArea->setWidget(m_containWidget);
	this->setCentralWidget(ui.scrollArea);
}

BatchWindow::~BatchWindow() 
{

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
	
}

void BatchWindow::on_actionGray_Scale_triggered()
{
	//auto magician(MagicianFactory::SharedMagicianFactory().GetMagicianByName("GrayScaler"));
	//for (auto &iter : m_iconList)
	//{
	//	iter->SetMag(magician);
	//	iter->DoMagic();
	//}
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

void BatchWindow::on_actionLeft_90_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void BatchWindow::on_actionRight_90_triggered()
{
	DO_PROCESS_AND_SHOW;
}

void BatchWindow::RemoveIcon(IconWidget* removeItem)
{
	m_iconList.remove(removeItem);
	m_layout->removeWidget(removeItem);
	delete removeItem;
}

void BatchWindow::OpenImage(IconWidget* item)
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
		auto iconImg = new IconWidget(QString::fromStdString(imgPath), this);
		m_iconList.push_back(iconImg);
		m_layout->addWidget(iconImg, 0, kCount++);
	}
}

void BatchWindow::AddImage(const std::list<std::string>& imgPathList)
{
	for (auto &path : imgPathList)
	{
		AddImage(path);
	}
}
