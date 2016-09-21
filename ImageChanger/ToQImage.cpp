#include "ImageChanger/ToQImage.h"
#include "DataStructure/Image.h"
#include <QImage>

void MatToQImage(const cv::Mat& mat, QImage& qImg)
{
	qImg = QImage((const unsigned char*)(mat.data), mat.cols, mat.rows, mat.cols*mat.channels(), QImage::Format_RGB888);
}
QImage ToQImage::DoChange(const Image& img, QImage& qImg)
{
	MatToQImage(img.GetMat(), qImg);
	return qImg;
}
