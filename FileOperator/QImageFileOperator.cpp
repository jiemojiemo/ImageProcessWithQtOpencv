#include "FileOperator/QImageFileOperator.h"

#include "DataStructure/MImage.h"

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

bool QImageFileOperator::Save( const MImage& img, const std::string& filename)
{
	assert(filename != "");

	QImage qImg(img.GetQImage());
	qImg.save(QString::fromStdString(filename));
	return true;
}

std::string QImageFileOperator::SaveAs( const MImage& img)
{
	QImage qImg(img.GetQImage());

	QString filename = QFileDialog::getSaveFileName(nullptr,
		QObject::tr("Save Image"),
		"",
		QObject::tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF")); //select path

	if (!filename.isEmpty())
	{
		if (!(qImg.save(filename))) //����ͼ��  
		{
			QMessageBox::information(nullptr,
				QObject::tr("Failed to save the image"),
				QObject::tr("Failed to save the image!"));
			return std::string();
		}
	}
	return filename.toStdString();
}

