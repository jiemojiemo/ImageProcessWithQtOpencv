#include "Contourer2.h"

#include "DataStructure/Image.h"
#include <opencv2\core.hpp>
#include "opencv2/highgui.hpp"
//#include "cv.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>

//http://blog.sina.com.cn/s/blog_76088a1f0101dis4.html
//http://blog.csdn.net/felix86/article/details/38121959
int  Contourer2Proc(cv::Mat& mat)
{
	cvtColor(mat, mat, CV_BGR2GRAY);//先灰度化
	IplImage* src; src = cvCreateImage(cvSize(mat.cols, mat.rows), 8, 1); IplImage ipltemp = mat; cvCopy(&ipltemp, src);//完全的imlImage进行复制
	if (!src)
	{
		printf("read data error!\n");
		return -1;
	}
	IplImage* dst = cvCreateImage(cvGetSize(src), 8, 3);
	IplImage *dsw = cvCreateImage(cvGetSize(src), 8, 1);
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq *first_contour = NULL;

	//turn the src image to a binary image    
	//cvThreshold(src, dsw, 125, 255, CV_THRESH_BINARY_INV);    
	cvThreshold(src, dsw, 100, 255, CV_THRESH_BINARY);

	cvFindContours(dsw, storage, &first_contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	cvZero(dst);
	int cnt = 0;
	for (; first_contour != 0; first_contour = first_contour->h_next)
	{
		cnt++;
		CvScalar color = CV_RGB(rand() & 255, rand() & 255, rand() & 255);
		cvDrawContours(dst, first_contour, color, color, 0, 2, CV_FILLED, cvPoint(0, 0));
		CvRect rect = cvBoundingRect(first_contour, 0);
		cvRectangle(dst, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), CV_RGB(255, 0, 0), 1, 8, 0);
	}
	cv::Mat temp = cv::cvarrToMat(dst);//iplImage转mat
	mat = temp.clone();//对mat硬拷贝
    //销毁窗口和图像存储  	
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseImage(&dsw);
	cvReleaseMemStorage(&storage);
	return 0;
#if 0
	//the parm. for cvFindContours  
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contour = 0;
	double maxarea = 0;
	//二值化  
	cvThreshold(src, src, 125, 255, CV_THRESH_BINARY);
	//提取轮廓  
	//cvFindContours(src, storage, &contour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	cvFindContours(src, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	cvZero(dst);//清空数组  
				/*CvSeq* _contour为了保存轮廓的首指针位置，因为随后contour将用来迭代*/
	CvSeq* _contour = contour;
	int maxAreaIdx = -1, iteratorIdx = 0, minarea=1;//n为面积最大轮廓索引，m为迭代索引  
	for (int iteratorIdx = 0; contour != 0; contour = contour->h_next, iteratorIdx++/*更新迭代索引*/)
	{
		double tmparea = fabs(cvContourArea(contour));
		if (tmparea > maxarea)
		{
			maxarea = tmparea;
			maxAreaIdx = iteratorIdx;
			continue;
		}
		//if (tmparea < minarea)
		//{
		//	//删除面积小于设定值的轮廓  
		//	cvSeqRemove(contour, 0);
		//	continue;
		//}
	//	CvRect aRect = cvBoundingRect(contour, 0);
		//if ((aRect.width / aRect.height)<whRatio)
		//{
		//	//删除宽高比例小于设定值的轮廓  
		//	cvSeqRemove(contour, 0);
		//	continue;
		//}
	//	CvScalar color1 = CV_RGB( rand()&255, rand()&255, rand()&255 );//创建一个色彩值  
		//CvScalar color = CV_RGB(0, 255, 255);  
		//max_level 绘制轮廓的最大等级。如果等级为0，绘制单独的轮廓。如果为1，绘制轮廓及在其后的相同的级别下轮廓。  
		//如果值为2，所有的轮廓。如果等级为2，绘制所有同级轮廓及所有低一级轮廓，诸此种种。  
		//如果值为负数，函数不绘制同级轮廓，但会升序绘制直到级别为abs(max_level)-1的子轮廓。   
		//cvDrawContours(dst, contour, color1, color1, -1, 1, 8);//绘制外部和内部的轮廓  
	}
	contour = _contour; /*int k=0;*/
						//统计剩余轮廓，并画出最大面积的轮廓  
	int count = 0;
	for (; contour != 0; contour = contour->h_next)
	{
		count++;
		double tmparea = fabs(cvContourArea(contour));
		if (tmparea == maxarea /*k==n*/)
		{
			/*CvScalar color = CV_RGB(255, 0, 0);
			cvDrawContours(dst, contour, color, color, -1, 1, 8);
			CvRect rect = cvBoundingRect(contour, 0);
			cvRectangle(dst, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), CV_RGB(255, 0, 0), 1, 8, 0);*/
			//怎么显示的在这改
			CvScalar color = CV_RGB(rand() & 255, rand() & 255, rand() & 255);
			cvDrawContours(dst, contour, color, color, 0, 2, CV_FILLED, cvPoint(0, 0));
			CvRect rect = cvBoundingRect(contour, 0);
			cvRectangle(dst, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), CV_RGB(255, 0, 0), 1, 8, 0);
		}
		/*k++;*/
	}
	printf("The total number of contours is:%d", count);
	cv::Mat temp = cv::cvarrToMat(dst);//iplImage转mat
	mat = temp.clone();//对mat硬拷贝
	//销毁窗口和图像存储  	
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return 0;
#endif // 0

}
void Contourer2::DoMagic(Image & img)
{
	Contourer2Proc(img.GetMat());
}