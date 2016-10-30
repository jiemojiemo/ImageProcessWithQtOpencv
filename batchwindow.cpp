#include "batchwindow.hpp"
#include "iconwidget.h"
#include "FileOperator/QImageBatchFileOperator.h"

#include <algorithm>

int kCount = 0;
BatchWindow::BatchWindow(QWidget * parent) : QMainWindow(parent) 
{
	m_layout = new QGridLayout;
	m_containWidget = new QWidget;

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
	}
	m_iconList.clear();
	
}

void BatchWindow::RemoveIcon(IconWidget* removeItem)
{
	m_iconList.remove(removeItem);
	m_layout->removeWidget(removeItem);
	int count = m_layout->count();
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
