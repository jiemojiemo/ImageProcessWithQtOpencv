#include "Magic/GrabCutor.h"
#include "imgproc.hpp"
#include "DataStructure/MImage.h"
#include <iostream>
#include "highgui.hpp"
REGISTER_INTO_FACTORY(GrabCutor);

int GrabCutorProc(cv::Mat& mat)
{
	// ����һ��ͼ��
	cv::Mat image = mat;
	if (!image.data)
	{
		std::cout << "���ܴ�ͼ��" << std::endl;
		return 0;
	}

	// ������������Ǳ��� 
	cv::Rect rectangle(20, 20, image.cols , image.rows - 10);

	cv::Mat result;
	//������ʱ�����������Ϊ�㷨���м����ʹ�ã�����care
	cv::Mat bgModel, fgModel;
	double tt = cv::getTickCount();
	// GrabCut �ֶ�
	cv::grabCut(image,    //����ͼ��
		result,   //�ֶν��
		rectangle,// ����ǰ���ľ��� 
		bgModel, fgModel, // ǰ��������
		10,        // ��������
		cv::GC_INIT_WITH_RECT); // �þ���
	tt = cv::getTickCount() - tt;
	printf("�㷨ִ��ִ��ʱ��:%g ms\n", tt / cv::getTickFrequency() * 1000);
	// �õ�������ǰ��������
	//�ȽϺ�������ֵΪGC_PR_FGD������
	cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
	// �������ͼ��
	cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
	imshow("result", result);
	cvWaitKey(0);
	imshow("foreground", foreground);
	cvWaitKey(0);
	//����ֵΪ GC_BGD=0����Ϊ����
	image.copyTo(foreground, result);
	imshow("foreground2", foreground);
	cvWaitKey(0);
}

void GrabCutor::DoMagic(MImage& img)
{
	GrabCutorProc(img.GetMat());
}