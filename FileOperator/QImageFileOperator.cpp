#include "FileOperator/QImageFileOperator.h"

#include "DataStructure/Image.h"

#include <QImage>
#include <QString>
#include <QFileDialog>
#include <QObject>
#include <QMessageBox>

#include <cassert>

std::string QImageFileOperator::Open()
{
	QString filename = QFileDialog::getOpenFileName(
		nullptr, QObject::tr("Open Image"), ".", QObject::tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
	return filename.toStdString();
}

bool QImageFileOperator::Save( const Image& img, const std::string& filename)
{
	assert(filename != "");

	QImage qImg(img.GetQImage());
	qImg.save(QString::fromStdString(filename));
	return true;
}

bool QImageFileOperator::SaveAs( const Image& img)
{
	QImage qImg(img.GetQImage());

	QString filename = QFileDialog::getSaveFileName(nullptr,
		QObject::tr("Save Image"),
		"",
		QObject::tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF")); //select path

	if (filename.isEmpty())
	{
		return false;
	}
	else
	{
		if (!(qImg.save(filename))) //±£´æÍ¼Ïñ  
		{
			QMessageBox::information(nullptr,
				QObject::tr("Failed to save the image"),
				QObject::tr("Failed to save the image!"));
			return false;
		}
	}
	return true;
}

