#include "ImageChanger/ImageToQImage.h"
#include "DataStructure/MImage.h"
#include "imgproc.hpp"
#include "highgui.hpp"
#include "ImageChanger/cvmatandqimage.h"
#include <QImage>

QImage MatToQImage(const cv::Mat& mat)
{
	return QtOcv::mat2Image(mat);
}
QImage ImageToQImage::DoChange(const MImage& img)
{
	return MatToQImage(img.GetMat());
}
