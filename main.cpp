#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>

//test sql
//#include "SQLite/SQLiteSelector.h"
//#include "SQLite/ImageModel.h"
//#include <QDebug>
#include "ImageDatabaseWindow.h"

#pragma comment(lib, "./SQLite/sqlite3_64.lib")
#pragma comment(lib, "./opencv/x64/vc14/lib/opencv_world310.lib")
#pragma comment(lib, "./opencv/x64/vc14/lib/opencv_world310d.lib")



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));


	MainWindow w;
	w.show();

	//BatchWindow batchWin;
	
	//batchWin.show();
	return a.exec();

	//SQLiteSelector<ImageModel> imagesSel("images.db");
	//auto res = imagesSel.SelectAll("images_tab");
	//for (auto& item : res)
	//{
	//}
}


