#pragma once
#include "common/common.h"
#include <string>

class Image;
class ImageFileOperator
{
	DISALLOW_COPY_AND_ASSIGN(ImageFileOperator);
public:
	ImageFileOperator() = default;
	~ImageFileOperator() = default;

	virtual std::string Open() = 0;
	virtual bool Save( const Image& img, const std::string& filename) = 0;
	virtual bool SaveAs( const Image& img) = 0;
};
