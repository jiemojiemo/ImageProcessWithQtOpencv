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
	cvtColor(mat, mat, CV_BGR2GRAY);//�ȻҶȻ�
	IplImage* src; src = cvCreateImage(cvSize(mat.cols, mat.rows), 8, 1); IplImage ipltemp = mat; cvCopy(&ipltemp, src);//��ȫ��imlImage���и���
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
	cv::Mat temp = cv::cvarrToMat(dst);//iplImageתmat
	mat = temp.clone();//��matӲ����
    //���ٴ��ں�ͼ��洢  	
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
	//��ֵ��  
	cvThreshold(src, src, 125, 255, CV_THRESH_BINARY);
	//��ȡ����  
	//cvFindContours(src, storage, &contour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	cvFindContours(src, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	cvZero(dst);//�������  
				/*CvSeq* _contourΪ�˱�����������ָ��λ�ã���Ϊ���contour����������*/
	CvSeq* _contour = contour;
	int maxAreaIdx = -1, iteratorIdx = 0, minarea=1;//nΪ����������������mΪ��������  
	for (int iteratorIdx = 0; contour != 0; contour = contour->h_next, iteratorIdx++/*���µ�������*/)
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
		//	//ɾ�����С���趨ֵ������  
		//	cvSeqRemove(contour, 0);
		//	continue;
		//}
	//	CvRect aRect = cvBoundingRect(contour, 0);
		//if ((aRect.width / aRect.height)<whRatio)
		//{
		//	//ɾ����߱���С���趨ֵ������  
		//	cvSeqRemove(contour, 0);
		//	continue;
		//}
	//	CvScalar color1 = CV_RGB( rand()&255, rand()&255, rand()&255 );//����һ��ɫ��ֵ  
		//CvScalar color = CV_RGB(0, 255, 255);  
		//max_level �������������ȼ�������ȼ�Ϊ0�����Ƶ��������������Ϊ1��������������������ͬ�ļ�����������  
		//���ֵΪ2�����е�����������ȼ�Ϊ2����������ͬ�����������е�һ��������������֡�  
		//���ֵΪ����������������ͬ�������������������ֱ������Ϊabs(max_level)-1����������   
		//cvDrawContours(dst, contour, color1, color1, -1, 1, 8);//�����ⲿ���ڲ�������  
	}
	contour = _contour; /*int k=0;*/
						//ͳ��ʣ��������������������������  
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
			//��ô��ʾ�������
			CvScalar color = CV_RGB(rand() & 255, rand() & 255, rand() & 255);
			cvDrawContours(dst, contour, color, color, 0, 2, CV_FILLED, cvPoint(0, 0));
			CvRect rect = cvBoundingRect(contour, 0);
			cvRectangle(dst, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), CV_RGB(255, 0, 0), 1, 8, 0);
		}
		/*k++;*/
	}
	printf("The total number of contours is:%d", count);
	cv::Mat temp = cv::cvarrToMat(dst);//iplImageתmat
	mat = temp.clone();//��matӲ����
	//���ٴ��ں�ͼ��洢  	
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return 0;
#endif // 0

}
void Contourer2::DoMagic(Image & img)
{
	Contourer2Proc(img.GetMat());
}