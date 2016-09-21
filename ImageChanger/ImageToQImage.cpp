#include "ImageChanger/ImageToQImage.h"
#include "DataStructure/Image.h"
#include "imgproc.hpp"
#include "highgui.hpp"
#include "ImageChanger/cvmatandqimage.h"
#include <QImage>

QImage MatToQImage(const cv::Mat& mat)
{
	return QtOcv::mat2Image(mat);
}
QImage ImageToQImage::DoChange(const Image& img)
{
	return MatToQImage(img.GetMat());
}
