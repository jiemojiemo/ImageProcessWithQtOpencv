#include "GrayScaler.h"
#include "imgproc.hpp"
#include "DataStructure/Image.h"

#include "highgui.h"

void GrayProc(cv::Mat& mat) {
	cvtColor(mat, mat, CV_BGR2GRAY);
}

void GrayScaler::DoMagic(Image & img)
{
	GrayProc(img.GetMat());
}
