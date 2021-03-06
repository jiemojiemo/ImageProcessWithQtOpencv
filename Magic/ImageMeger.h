#pragma once
#include "common/common.h"
#include <core.hpp>
#include <list>
#include <vector>
class ImageMerger
{
	DISALLOW_COPY_AND_ASSIGN(ImageMerger);
public:
	ImageMerger();
	virtual ~ImageMerger();
	void AddImage(const cv::Mat& img);
	void RemoveImage(int index);
	cv::Mat MergeImages();
	

	virtual void Pretreat();
	virtual void ConstructImageArray();
	virtual void InitDstImage()=0;
	virtual void ConstructDstImage()=0;
private:
	void PretreatByResize(cv::Mat& mat);
	void DeletePImgArray();
protected:
	std::vector<cv::Mat> m_imgArray;
	std::vector<IplImage*> m_pImgArray;
	IplImage* m_dstImage;
};