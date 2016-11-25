#include "Magic/GrabCutor.h"
#include "imgproc.hpp"
#include "DataStructure/MImage.h"
#include <iostream>
#include "highgui.hpp"
REGISTER_INTO_FACTORY(GrabCutor);

int GrabCutorProc(cv::Mat& mat)
{
	// 打开另一幅图像
	cv::Mat image = mat;
	if (!image.data)
	{
		std::cout << "不能打开图像！" << std::endl;
		return 0;
	}

	// 矩形外的像素是背景 
	cv::Rect rectangle(20, 20, image.cols , image.rows - 10);

	cv::Mat result;
	//两个临时矩阵变量，作为算法的中间变量使用，不用care
	cv::Mat bgModel, fgModel;
	double tt = cv::getTickCount();
	// GrabCut 分段
	cv::grabCut(image,    //输入图像
		result,   //分段结果
		rectangle,// 包含前景的矩形 
		bgModel, fgModel, // 前景、背景
		10,        // 迭代次数
		cv::GC_INIT_WITH_RECT); // 用矩形
	tt = cv::getTickCount() - tt;
	printf("算法执行执行时间:%g ms\n", tt / cv::getTickFrequency() * 1000);
	// 得到可能是前景的像素
	//比较函数保留值为GC_PR_FGD的像素
	cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
	// 产生输出图像
	cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
	imshow("result", result);
	cvWaitKey(0);
	imshow("foreground", foreground);
	cvWaitKey(0);
	//背景值为 GC_BGD=0，作为掩码
	image.copyTo(foreground, result);
	imshow("foreground2", foreground);
	cvWaitKey(0);
}

void GrabCutor::DoMagic(MImage& img)
{
	GrabCutorProc(img.GetMat());
}