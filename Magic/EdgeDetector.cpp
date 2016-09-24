#include "EdgeDetector.h"
#include "imgproc.hpp"
#include "DataStructure/Image.h"

REGISTER_INTO_FACTORY(EdgeDetector);

void SobelProc(cv::Mat& mat)
{
	cv::Sobel(mat, mat, mat.depth(), 1, 1);
}

void EdgeDetector::DoMagic(Image& img)
{
	SobelProc(img.GetMat());
}

