#include "DataStructure\Image.h"

//Openvc
#include "imgproc.hpp"

Image::Image(const cv::Mat & mat):
	m_mat(mat)
{

}

Image & Image::operator=(const cv::Mat & mat)
{
	if (&m_mat == &mat)
		return *this;
	
	this->SetCVMat(mat);
	return *this;
}

void Image::SetCVMat(const cv::Mat & mat)
{
	cv::cvtColor(mat, m_mat, CV_BGR2RGB);
}
