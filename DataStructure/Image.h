#pragma once
#include <core.hpp>

class EdgeDetector;
class cv::Mat;
class Image
{
	friend class EdgeDetector;
public:
	Image() = default;
	Image(const cv::Mat& mat);
	Image& operator=(const cv::Mat& mat);
	~Image() = default;
public:
	const cv::Mat& GetMat()const { return m_mat; }
	cv::Mat& GetMat() { return m_mat; }

	void SetCVMat(const cv::Mat& mat);
private:
	cv::Mat m_mat;
};

