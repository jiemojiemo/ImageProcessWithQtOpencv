#pragma once
#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>

#include "ui_batchwindow.h"

#include <list>
#include <string>

class IconWidget;
class ImageBox;
class MImage;
class BatchWindow : public QMainWindow {
	Q_OBJECT

public:
	BatchWindow(QWidget * parent = Q_NULLPTR);
	~BatchWindow();

private slots:
	//File
	void on_actionOpen_New_Folder_triggered();
	void on_actionOpen_New_Image_triggered();
	void on_actionClear_All_triggered();

	void RemoveIcon(IconWidget* removeItem);
	void OpenImage(IconWidget* item);

private:
	bool IsExitFilePath(const std::string& imgPath);
	void AddImage(const std::string& imgPath);
	void AddImage(const std::list<std::string>& imgPathList);



private:
	Ui::BatchWindow ui;
	QGridLayout* m_layout;
	QWidget* m_containWidget;
	std::list<IconWidget*> m_iconList;
	//std::list<MImage*> m_imgList;
	ImageBox* m_imgBox;
};
