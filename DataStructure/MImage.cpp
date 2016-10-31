#include "DataStructure\MImage.h"
#include "ImageChanger\cvmatandqimage.h"
#include "Magic/Magician.h"

//Openvc
#include "imgproc.hpp"
#include "highgui.hpp"

MImage::MImage() :Image()
{

}

MImage::MImage(const std::string& path): MImage(QString::fromStdString(path))
{
}

MImage::MImage(const QString& path):m_qImg(path)
{
	m_mat = QtOcv::image2Mat(m_qImg);
}

void MImage::DoMagic()
{
	if (m_mag != nullptr)
	{
		m_mag->DoMagic(*this);
		UpdateImage();

	}
}

void MImage::SetMat(const cv::Mat& val)
{
	m_mat = val;
	m_qImg = QtOcv::mat2Image(m_mat);
}


void MImage::SetQImage(const QImage& qImg)
{
	m_qImg = qImg;
	m_mat = QtOcv::image2Mat(m_qImg);
}

void MImage::UpdateImage()
{
	if (m_isMat)
		m_qImg = QtOcv::mat2Image(m_mat);
	else
		m_mat = QtOcv::image2Mat(m_qImg);
}

MImage& MImage::operator=(const QImage& qImg)
{
	if (&m_qImg == &qImg)
		return *this;

	this->SetQImage(qImg);
	return *this;
}

MImage & MImage::operator=(const cv::Mat & mat)
{
	if (&m_mat == &mat)
		return *this;

	this->SetMat(mat);
	return *this;
}

