#include "Magic/HorizontalMerger.h"

void HorizontalMerger::InitDstImage()
{
	int sw = m_pImgArray[0]->width;
	int sh = m_pImgArray[0]->height;
	m_dstImage = cvCreateImage(cvSize(sw * m_pImgArray.size(), sh), m_pImgArray[0]->depth, m_pImgArray[0]->nChannels);
	cvZero(m_dstImage);
}

void HorizontalMerger::ConstructDstImage()
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
}
