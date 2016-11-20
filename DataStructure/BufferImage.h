#pragma once

#include "MImage.h"
#include <list>

class BufferImage : public MImage
{
public:
	BufferImage();
	BufferImage(const std::string& path);
	BufferImage(const QString& path);
	BufferImage& operator=(const cv::Mat& mat);
	BufferImage& operator=(const QImage& qImg);
	virtual void DoMagic();
	void Undo();
	bool IsAbleToUndo();
private:
	void SaveMatToBuffer();
private:
	std::list<cv::Mat> m_bufferImgList;

	static const int kUndoCount = 10;
};