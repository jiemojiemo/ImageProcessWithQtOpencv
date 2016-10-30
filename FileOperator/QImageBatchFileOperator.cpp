#include "FileOperator/QImageBatchFileOperator.h"

#include <QDir>
#include <QFileDialog>

std::list<std::string> QImageBatchFileOperator::OpenFolder()
{
	auto path = QFileDialog::getExistingDirectory(NULL, QObject::tr("Choose Folder"), "D:\\", QFileDialog::ShowDirsOnly);
	QDir *dir = new QDir(path);
	QStringList filter;
	filter << "*.jpg";
	filter << "*.png";
	filter << "*.bmp";
	filter << "*.jpeg";
	dir->setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));

	std::list<std::string> filenameList;
	for (int i = 0; i < fileInfo->count(); ++i)
	{
		filenameList.push_back(fileInfo->at(i).filePath().toStdString());
	}

	return filenameList;
}

