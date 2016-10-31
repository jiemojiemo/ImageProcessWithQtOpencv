#pragma once
#include <core.hpp>
#include <QImage>
#include <memory>
#include "Magic/Magician.h"
#include "DataStructure/Image.h"
#include <string>

class MImage : public Image
{
public:
	MImage();
	MImage(const std::string& path);
	MImage(const QString& path);
	MImage& operator=(const cv::Mat& mat);
	MImage& operator=(const QImage& qImg);
	~MImage() = default;

	virtual void DoMagic();



	const cv::Mat& GetMat()const { return m_mat; }
	cv::Mat& GetMat() { m_isMat=true; return m_mat; }
	inline void SetMat(const cv::Mat& val);

	const QImage& GetQImage()const { return m_qImg; }
	QImage& GetQImage() { m_isMat=false; return m_qImg; }
	inline void SetQImage(const QImage& val);

	void SetMag(std::unique_ptr<Magician>& val) { m_mag = std::move(val); }
private:
	void UpdateImage();

private:
	cv::Mat m_mat;
	QImage m_qImg;
	bool m_isMat;
	std::unique_ptr<Magician> m_mag;
};

