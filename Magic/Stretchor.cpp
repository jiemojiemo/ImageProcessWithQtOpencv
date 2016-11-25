#include "Stretchor.h"

#include "DataStructure/MImage.h"
#include <opencv2\core.hpp>
#include "opencv2/highgui.hpp"
//#include "cv.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
REGISTER_INTO_FACTORY(Stretchor);
/*************************************************
Function:
Description:     因为摄像头图像质量差，需要根据直方图进行图像增强，
将图像灰度的域值拉伸到0-255
Calls:
Called By:
Input:           单通道灰度图像
Output:          同样大小的单通道灰度图像
Return:
Others:           http://www.xiaozhou.net/ReadNews.asp?NewsID=771
DATE:               2007-1-5
*************************************************/
void ImageStretchByHistogram(cv::Mat& mat)
{
	IplImage* dst; dst = cvCreateImage(cvSize(mat.cols, mat.rows), 8, 1); //IplImage ipltemp = mat; cvCopy(&ipltemp, dst);//完全的imlImage进行复制
	cv::cvtColor(mat, mat, CV_BGR2GRAY);//先灰度化
	IplImage* src; src = cvCreateImage(cvSize(mat.cols, mat.rows), 8, 1); IplImage ipltemp2 = mat; cvCopy(&ipltemp2, src);//完全的imlImage进行复制
																								//p[]存放图像各个灰度级的出现概率；
																								//p1[]存放各个灰度级之前的概率和，用于直方图变换；
																								//num[]存放图象各个灰度级出现的次数;

	assert(src->width == dst->width);
	float p[256], p1[256], num[256];
	//清空三个数组
	memset(p, 0, sizeof(p));
	memset(p1, 0, sizeof(p1));
	memset(num, 0, sizeof(num));

	int height = src->height;
	int width = src->width;
	long wMulh = height * width;

	//求存放图象各个灰度级出现的次数
	// to do use openmp
	for (int x = 0; x < src->width; x++) {
		for (int y = 0; y < src->height; y++) {
			uchar v = ((uchar*)(src->imageData + src->widthStep*y))[x];
			num[v]++;
		}
	}

	//求存放图像各个灰度级的出现概率
	for (int i = 0; i < 256; i++)
	{
		p[i] = num[i] / wMulh;
	}

	//求存放各个灰度级之前的概率和
	for (int i = 0; i < 256; i++)
	{
		for (int k = 0; k <= i; k++)
			p1[i] += p[k];
	}
	//图像增强
	for (int i = 0; i < src->height; i++)
	{		
		for (int j = 0; j < src->width; j++)
		{
			((uchar*)(i * dst->widthStep + dst->imageData))[j] = p1[((uchar*)(i * src->widthStep + src->imageData))[j]] * 255 + 0.5;
		}
	}
# if 0
	//直方图变换
	// to do use openmp
	for (int x = 0; x < src->width; x++) {
		for (int y = 0; y < src->height; y++) {
			uchar v = ((uchar*)(src->imageData + src->widthStep*y))[x];
			((uchar*)(dst->imageData + dst->widthStep*y))[x] = p1[v] * 255 + 0.5;
		}
	}
#endif
	cv::Mat temp = cv::cvarrToMat(dst);//iplImage转mat
	mat = temp.clone();//对mat硬拷贝
	cvWaitKey(0); //等待按键
	//销毁窗口和图像存储  	
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	
}

void Stretchor::DoMagic(MImage& img)
{
	ImageStretchByHistogram(img.GetMat());
}

