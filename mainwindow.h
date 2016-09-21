#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DataStructure/Image.h"

#include "highgui.hpp"
#include <QMainWindow>

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
    void on_actionOpen_triggered();

    void on_actionEdge_Detect_triggered();

    void on_actionClose_triggered();

	void on_actionSave_triggered();

	void on_actionSave_As_triggered();

	void on_actionLeft_90_triggered();

	void on_actionRight_90_triggered();

private:
    QString GetFilename();
    void ReadImage(const QString& filename);

    void ShowImage();
    void ShowImageInLabel(const QImage& img);
    void ShowImageInGraphicsView(const QImage& qImg);
	void ShowImageInGraphicsView(const Image& img);
	void ShowImageInGraphicsView();
private:
    Ui::MainWindow *ui;
    QImage m_qtImg;
	Image m_img;
};

#endif // MAINWINDOW_H
