#include "Magic/ImageMeger.h"
#include "imgproc.hpp"
#include "highgui.h"

ImageMerger::ImageMerger():m_dstImage(nullptr)
{

}

ImageMerger::~ImageMerger()
{
	this->DeletePImgArray();
}

void ImageMerger::AddImage(const cv::Mat& img)
{
	m_imgArray.push_back(img);
}

void ImageMerger::RemoveImage(int index)
{
	if (index > 0 && index < m_imgArray.size())
	{
		auto iter = m_imgArray.begin();
		advance(iter, index);
		m_imgArray.erase(iter);
	}
}

cv::Mat ImageMerger::MergeImages()
{
	Pretreat();
	ConstructImageArray();
	ConstructDstImage();
	cv::Mat img = cv::cvarrToMat(m_dstImage, true);
	return img;
}

void ImageMerger::Pretreat()
{
	for (auto& item : m_imgArray)
	{
		PretreatByResize(item);
	}
}

void ImageMerger::ConstructImageArray()
{

	//first delete m_pImageArray
	this->DeletePImgArray();

	//resize and init
	auto imgsCount = m_imgArray.size();
	m_pImgArray.resize(imgsCount,nullptr);
	for (int i = 0; i < imgsCount; ++i)
	{
		m_pImgArray[i] = new IplImage(m_imgArray[i]);
	}
}

void ImageMerger::InitDstImage()
{
	int sw = m_pImgArray[0]->width;
	int sh = m_pImgArray[0]->height;
	m_dstImage = cvCreateImage(cvSize(sw * m_pImgArray.size(), sh), m_pImgArray[0]->depth, m_pImgArray[0]->nChannels);
	cvZero(m_dstImage);
}

void ImageMerger::ConstructDstImage()
{
	InitDstImage();

	int sw = m_pImgArray[0]->width;
	int sh = m_pImgArray[0]->height;
	auto imgsCount = m_imgArray.size();
	for (int i = 0; i < imgsCount; ++i)
	{
		cvSetImageROI(m_dstImage, cvRect(i*sw, 0, sw, sh));
		cvCopy(m_pImgArray[i], m_dstImage);
		cvResetImageROI(m_dstImage);
	}
	//cvNamedWindow("dstImg");
	//cvShowImage("dstImg", m_dstImage);
}

void ImageMerger::PretreatByResize(cv::Mat& mat)
{
	auto dsize = cv::Size(256,256);
	cv::resize(mat, mat, dsize, 0, 0, cv::INTER_CUBIC);
}

void ImageMerger::DeletePImgArray()
{
	for (int i = 0; i < m_pImgArray.size(); ++i)
	{
		if (m_pImgArray[i] != nullptr)
		{
			delete m_pImgArray[i];
			m_pImgArray[i] = nullptr;
		}
	}
}

