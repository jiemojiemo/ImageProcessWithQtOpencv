#include "DataStructure\Image.h"
#include "ImageChanger\cvmatandqimage.h"
#include "Magic/Magician.h"

//Openvc
#include "imgproc.hpp"
#include "highgui.hpp"

Image::Image() :m_mag(nullptr)
{

}

void Image::DoMagic()
{
	if (m_mag != nullptr)
	{
		m_mag->DoMagic(*this);
		UpdateImage();

	}
}

void Image::SetMat(const cv::Mat& val)
{
	m_mat = val;
	m_qImg = QtOcv::mat2Image(m_mat);
}


void Image::SetQImage(const QImage& qImg)
{
	m_qImg = qImg;
	m_mat = QtOcv::image2Mat(m_qImg);
}

void Image::UpdateImage()
{
	if (m_isMat)
		m_qImg = QtOcv::mat2Image(m_mat);
	else
		m_mat = QtOcv::image2Mat(m_qImg);
}

Image& Image::operator=(const QImage& qImg)
{
	if (&m_qImg == &qImg)
		return *this;

	this->SetQImage(qImg);
	return *this;
}

Image & Image::operator=(const cv::Mat & mat)
{
	if (&m_mat == &mat)
		return *this;

	this->SetMat(mat);
	return *this;
}

