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
Description:     ��Ϊ����ͷͼ���������Ҫ����ֱ��ͼ����ͼ����ǿ��
��ͼ��Ҷȵ���ֵ���쵽0-255
Calls:
Called By:
Input:           ��ͨ���Ҷ�ͼ��
Output:          ͬ����С�ĵ�ͨ���Ҷ�ͼ��
Return:
Others:           http://www.xiaozhou.net/ReadNews.asp?NewsID=771
DATE:               2007-1-5
*************************************************/
void ImageStretchByHistogram(cv::Mat& mat)
{
	IplImage* dst; dst = cvCreateImage(cvSize(mat.cols, mat.rows), 8, 1); //IplImage ipltemp = mat; cvCopy(&ipltemp, dst);//��ȫ��imlImage���и���
	cv::cvtColor(mat, mat, CV_BGR2GRAY);//�ȻҶȻ�
	IplImage* src; src = cvCreateImage(cvSize(mat.cols, mat.rows), 8, 1); IplImage ipltemp2 = mat; cvCopy(&ipltemp2, src);//��ȫ��imlImage���и���
																								//p[]���ͼ������Ҷȼ��ĳ��ָ��ʣ�
																								//p1[]��Ÿ����Ҷȼ�֮ǰ�ĸ��ʺͣ�����ֱ��ͼ�任��
																								//num[]���ͼ������Ҷȼ����ֵĴ���;

	assert(src->width == dst->width);
	float p[256], p1[256], num[256];
	//�����������
	memset(p, 0, sizeof(p));
	memset(p1, 0, sizeof(p1));
	memset(num, 0, sizeof(num));

	int height = src->height;
	int width = src->width;
	long wMulh = height * width;

	//����ͼ������Ҷȼ����ֵĴ���
	// to do use openmp
	for (int x = 0; x < src->width; x++) {
		for (int y = 0; y < src->height; y++) {
			uchar v = ((uchar*)(src->imageData + src->widthStep*y))[x];
			num[v]++;
		}
	}

	//����ͼ������Ҷȼ��ĳ��ָ���
	for (int i = 0; i < 256; i++)
	{
		p[i] = num[i] / wMulh;
	}

	//���Ÿ����Ҷȼ�֮ǰ�ĸ��ʺ�
	for (int i = 0; i < 256; i++)
	{
		for (int k = 0; k <= i; k++)
			p1[i] += p[k];
	}
	//ͼ����ǿ
	for (int i = 0; i < src->height; i++)
	{		
		for (int j = 0; j < src->width; j++)
		{
			((uchar*)(i * dst->widthStep + dst->imageData))[j] = p1[((uchar*)(i * src->widthStep + src->imageData))[j]] * 255 + 0.5;
		}
	}
# if 0
	//ֱ��ͼ�任
	// to do use openmp
	for (int x = 0; x < src->width; x++) {
		for (int y = 0; y < src->height; y++) {
			uchar v = ((uchar*)(src->imageData + src->widthStep*y))[x];
			((uchar*)(dst->imageData + dst->widthStep*y))[x] = p1[v] * 255 + 0.5;
		}
	}
#endif
	cv::Mat temp = cv::cvarrToMat(dst);//iplImageתmat
	mat = temp.clone();//��matӲ����
	cvWaitKey(0); //�ȴ�����
	//���ٴ��ں�ͼ��洢  	
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	
}

void Stretchor::DoMagic(MImage& img)
{
	ImageStretchByHistogram(img.GetMat());
}

