#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DataStructure/MImage.h"
#include "DataStructure/BufferImage.h"

#include "highgui.hpp"
#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsScene>

class ImageDatabaseWindow;
class BatchWindow;
class InputTextDialog;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	//File
    void on_actionOpen_triggered();
    void on_actionClose_triggered();
	void on_actionSave_triggered();
	void on_actionSave_As_triggered();
	void on_actionUndo_triggered();
	void on_actionBatching_triggered();
	void on_actionImage_Database_triggered();
	void on_actionShare_To_Weibo_triggered();
	//Rotate
	void on_actionLeft_90_triggered();
	void on_actionRight_90_triggered();
	//Process
    void on_actionEdge_Detect_triggered();
	void on_actionGray_Scale_triggered();
	void on_actionOil_triggered();
	void on_actionStrech_triggered();
	void on_actionEmboss_triggered();
	void on_actionCarve_triggered();
	//AddText
	void on_actionHorizontal_Text_triggered();
	//void on_actionVertical_Text_triggered();

	void ReceiveImage(cv::Mat& img);
	void ReceiveImage(QImage& img);
private:
	QString GetText();
    QString GetFilename();
	void PaintTextOnImage(const QString& text);
    void ReadImage(const QString& filename);

    void ShowImageInGraphicsView(const QImage& qImg);
	void ShowImageInGraphicsView(const MImage& img);
	void ShowImage(const MImage& img);

	void InitUi();
	void AdjustSize(int witdth=700, int height=600);
	void SetLayout();

	void SetNewImageState();
	void SetNoImageState();
	void SetFileActionsDisable(bool b=false);
	void SetProcessDisabled(bool b=false);
	void SetRotateDisabled(bool b = false);
	void SetAddTextDisable(bool b = false);
private:
    Ui::MainWindow *ui;
	QGridLayout* m_layout;
	QGraphicsScene* m_graphicsScene;
	//MImage m_img;
	BufferImage m_img;
	BatchWindow* m_batchWin;
	ImageDatabaseWindow* m_databaseWin;
	InputTextDialog* m_textWin;
	static const int kMinWinWidth = 700;
	static const int kMinWinHeight = 600;
};

#endif // MAINWINDOW_H
