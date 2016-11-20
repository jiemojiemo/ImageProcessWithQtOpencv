#include "DataStructure/BufferImage.h"
#include <highgui.h>
BufferImage::BufferImage() :MImage()
{

}

BufferImage::BufferImage(const std::string& path):MImage(path)
{
}

BufferImage::BufferImage(const QString& path):MImage(path)
{

}

BufferImage& BufferImage::operator=(const cv::Mat& mat)
{
	MImage::operator=(mat);
	return *this;
}

BufferImage& BufferImage::operator=(const QImage& qImg)
{
	MImage::operator=(qImg);

	return *this;
}

void BufferImage::DoMagic()
{
	this->SaveMatToBuffer();
	MImage::DoMagic();
}

void BufferImage::Undo()
{
	if (this->IsAbleToUndo())
	{
		SetMat(m_bufferImgList.front());
		m_bufferImgList.pop_front();
	}
}

bool BufferImage::IsAbleToUndo()
{
	return !m_bufferImgList.empty();
}

void BufferImage::SaveMatToBuffer()
{
	if (m_bufferImgList.size() > kUndoCount)
	{
		m_bufferImgList.pop_front();
	}
	m_bufferImgList.push_front(this->GetMat().clone());
}
