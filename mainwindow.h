#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DataStructure/MImage.h"
#include "DataStructure/BufferImage.h"

#include "highgui.hpp"
#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsScene>

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
	void on_actionBatching_triggered();
	//Rotate
	void on_actionLeft_90_triggered();
	void on_actionRight_90_triggered();
	//Process
    void on_actionEdge_Detect_triggered();
	void on_actionGray_Scale_triggered();
	void on_actionOil_triggered();
	void on_actionContour_triggered();
	void on_actionUndo_triggered();

	void ReceiveImage(cv::Mat& img);
private:
    QString GetFilename();
    void ReadImage(const QString& filename);

    void ShowImageInGraphicsView(const QImage& qImg);
	void ShowImageInGraphicsView(const MImage& img);
	void ShowImage(const MImage& img);

	void InitUi();
	void AdjustSize(int witdth=700, int height=600);
	void SetLayout();

	void SetNewImageState();
	void SetFileActionsDisable(bool b=false);
	void SetProcessDisabled(bool b=false);
	void SetRotateDisabled(bool b = false);
private:
    Ui::MainWindow *ui;
	QGridLayout* m_layout;
	QGraphicsScene* m_graphicsScene;
	//MImage m_img;
	BufferImage m_img;
	static const int kMinWinWidth = 700;
	static const int kMinWinHeight = 600;
};

#endif // MAINWINDOW_H
