#include "Magic\GrayScaler.h"
#include "imgproc.hpp"
#include "DataStructure/Image.h"

REGISTER_INTO_FACTORY(GrayScaler);

void BRG2Gray(cv::Mat& mat)
{
	cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);
}

void GrayScaler::DoMagic(Image & img)
{
	BRG2Gray(img.GetMat());
}
