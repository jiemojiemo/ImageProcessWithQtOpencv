#pragma once
#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <core.hpp>
#include "ui_batchwindow.h"

#include <list>
#include <string>

class IconWidget;
class ImageBox;
class MImage;
class ImageMerger;
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
	void on_actionUndo_triggered();
	void on_actionVertical_Merge_triggered();
	void on_actionHorizontal_Merge_triggered();

	//Process
	void on_actionGray_Scale_triggered();
	void on_actionEdge_Detect_triggered();
	void on_actionOil_triggered();
	//Rotate
	void on_actionLeft_90_triggered();
	void on_actionRight_90_triggered();

	void RemoveIcon(IconWidget* removeItem);
	void OpenImage(IconWidget* item);
signals:
	void SentMat(cv::Mat& mat);
private:
	bool IsExitFilePath(const std::string& imgPath);
	void AddImage(const std::string& imgPath);
	void AddImage(const std::list<std::string>& imgPathList);
	int GetWidgetRowIndex();
	int GetWidgetColIndex();
	void MergeImages(ImageMerger* merge);


private:
	Ui::BatchWindow ui;
	QGridLayout* m_layout;
	QWidget* m_containWidget;
	std::list<IconWidget*> m_iconList;
	//std::list<MImage*> m_imgList;
	ImageBox* m_imgBox;
	const static int kWinWidth;
	const static int kWinHeight;
};
