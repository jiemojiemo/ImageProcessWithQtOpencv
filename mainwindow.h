#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_ID_BUT_READ_clicked();
    void on_ID_BUT_PROC_clicked();

    void on_actionOpen_triggered();

    void on_actionEdge_Detect_triggered();

    void on_actionClose_triggered();

private:
    QString GetFilename();
    void ReadImage(const QString& filename);

    void CVMatToQImage(const cv::Mat& mat, QImage& img);
    void ShowImage();
    void ShowImageInLabel(const QImage& img);
    void ShowImageInGraphicsView(const QImage& img);
private:
    Ui::MainWindow *ui;
    cv::Mat m_img;
    QImage m_qtImg;
};

#endif // MAINWINDOW_H
