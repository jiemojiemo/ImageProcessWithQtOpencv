#include "EdgeDetector.h"
#include "imgproc.hpp"
#include "DataStructure/Image.h"

void SobelProc(cv::Mat& mat)
{
	cv::Sobel(mat, mat, mat.depth(), 1, 1);
}

void EdgeDetector::DoMagic(Image& img)
{
	SobelProc(img.GetMat());
}

