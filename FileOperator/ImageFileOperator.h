#pragma once
#include "common/common.h"
#include <string>

class MImage;
class ImageFileOperator
{
	DISALLOW_COPY_AND_ASSIGN(ImageFileOperator);
public:
	ImageFileOperator() = default;
	~ImageFileOperator() = default;

	virtual std::string Open() = 0;
	virtual bool Save( const MImage& img, const std::string& filename) = 0;
	virtual std::string SaveAs( const MImage& img) = 0;
};
