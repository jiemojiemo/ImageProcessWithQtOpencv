#pragma once
#include "batchwindow.hpp"
#include <string>
class ImageDatabaseWindow : public BatchWindow
{
	Q_OBJECT

public:
	ImageDatabaseWindow(const std::string& dbPath,const std::string& tabName,
		QWidget * parent = Q_NULLPTR);
	~ImageDatabaseWindow();
protected slots:
	virtual void ClickImage(IconWidget* item);

private:
	void LoadImagesFromDB();

private:
	std::string m_dbPath;
	std::string m_tabName;
};