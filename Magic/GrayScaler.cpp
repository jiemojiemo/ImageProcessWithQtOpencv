#include "GrayScaler.h"
#include "imgproc.hpp"
#include "DataStructure/Image.h"
#include "opencv2/highgui.hpp"
//#include "cv.h"
#include "opencv2/opencv.hpp"
void GrayProc(cv::Mat& mat)
{
	//cvCvtColor(src,des,CV_BGR2GRAY) 
	cvtColor(mat, mat, CV_BGR2GRAY);
	//imshow("1", mat);
	//imwrite("2.jpg", mat);
}

void GrayScaler::DoMagic(Image & img)
{
	GrayProc(img.GetMat());
}
