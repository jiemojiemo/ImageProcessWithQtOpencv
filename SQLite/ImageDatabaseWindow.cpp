#include "ImageDatabaseWindow.h"
#include "SQLite/SQLiteSelector.h"
#include "SQLite/ImageModel.h"
#include "iconwidget.h"
#include "ImageBox.h"

#include "common/common.h"

ImageDatabaseWindow::ImageDatabaseWindow(const std::string& dbPath, 
	const std::string& tabName, QWidget * parent /*= Q_NULLPTR*/):
	BatchWindow(parent),
	m_dbPath(dbPath),
	m_tabName(tabName)
{
	ui.menubar->setVisible(false);

	LoadImagesFromDB();

	//connect(this, SIGNAL(SentQImg(QImage& img)), parent, SLOT(ReceiveImage(QImage& img)));
	connect(this, SIGNAL(SentMat(cv::Mat&)), parent, SLOT(ReceiveImage(cv::Mat&)));
}

ImageDatabaseWindow::~ImageDatabaseWindow()
{

}

void ImageDatabaseWindow::ClickImage(IconWidget* item)
{
	emit this->SentMat(item->GetMat());
}

void ImageDatabaseWindow::LoadImagesFromDB()
{
	auto selector = new SQLiteSelector<ImageModel>(m_dbPath);
	ON_SCOPE_EXIT([&selector]() {delete selector; });

	auto imagesArray = selector->SelectAll(m_tabName);

	for (auto& item : imagesArray)
	{
		this->AddImage(item.GetFullPath());
	}

}
