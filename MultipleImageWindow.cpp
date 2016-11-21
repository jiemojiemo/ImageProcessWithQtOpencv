#include "MultipleImageWindow.h"
#include "iconwidget.h"

MultipleImageWindow::MultipleImageWindow(QWidget * parent /*= Q_NULLPTR*/):QMainWindow(parent)
{
	m_layout = new QGridLayout(this);
	m_containWidget = new QWidget(this);
}

MultipleImageWindow::~MultipleImageWindow()
{

}

void MultipleImageWindow::AddImage(const std::string& imgPath)
{

}

void MultipleImageWindow::AddImage(const std::list<std::string>& imgPathList)
{
	for (auto &path : imgPathList)
	{
		AddImage(path);
	}
}

bool MultipleImageWindow::IsExitFilePath(const std::string& imgPath)
{
	if (!IsExitFilePath(imgPath))
	{
		auto iconImg = new IconWidget(QString::fromStdString(imgPath), this);
		m_iconList.push_back(iconImg);
		m_layout->addWidget(iconImg, GetWidgetRowIndex(), GetWidgetColIndex());
	}
}
