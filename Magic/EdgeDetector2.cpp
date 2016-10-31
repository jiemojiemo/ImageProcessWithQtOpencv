#include "EdgeDetector2.h"
#include "imgproc.hpp"
#include "DataStructure/MImage.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

REGISTER_INTO_FACTORY(EdgeDetector2);

void ContourorProc(cv::Mat& mat)
{
	cv::cvtColor(mat, mat, CV_BGR2GRAY);

	cv::Mat contours;
	cv::Canny(mat, contours, 125, 350);
	threshold(contours, contours, 128, 255, cv::THRESH_BINARY);
	mat = contours;
}

void EdgeDetector2::DoMagic(MImage& img)
{
	ContourorProc(img.GetMat());
}

