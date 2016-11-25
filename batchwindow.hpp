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
class InputTextDialog;
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
	void on_actionSave_triggered();
	void on_actionSave_As_triggered();

	//Merge
	void on_actionVertical_Merge_triggered();
	void on_actionHorizontal_Merge_triggered();

	//Process
	void on_actionGray_Scale_triggered();
	void on_actionEdge_Detect_triggered();
	void on_actionOil_triggered();
	void on_actionEmboss_triggered();
	void on_actionCarve_triggered();
	void on_actionStrech_triggered();
	//Rotate
	void on_actionLeft_90_triggered();
	void on_actionRight_90_triggered();
	//Add Text
	void on_actionHorizontal_Text_triggered();
protected slots:
	void RemoveIcon(IconWidget* removeItem);
	virtual void ClickImage(IconWidget* item);
signals:
	void SentMat(cv::Mat& mat);
protected:
	bool IsExitFilePath(const std::string& imgPath);
	void AddImage(const std::string& imgPath);
	void AddImage(const std::list<std::string>& imgPathList);
	int GetWidgetRowIndex()const;
	int GetWidgetColIndex()const;
	void MergeImages(ImageMerger* merge);
	void SetNewImageState();
	void SetNoImageState();
	void SetProcessDisable(bool b = true);
	void SetRotateDisable(bool b = true);
	void SetMergeDisable(bool b = true);
	void SetAddTextDiable(bool b = true);

	QString GetNewNameForSaveAs(const QString& name)const;
	QString GetText();


protected:
	Ui::BatchWindow ui;
	QGridLayout* m_layout;
	QWidget* m_containWidget;
	std::list<IconWidget*> m_iconList;
	//std::list<MImage*> m_imgList;
	ImageBox* m_imgBox;
	InputTextDialog* m_textWin;
	const static int kWinWidth;
	const static int kWinHeight;
};
