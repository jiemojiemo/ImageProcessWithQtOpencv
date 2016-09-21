#pragma once

#include "common/common.h"

class Image;
class QImage;

class ImageToQImage
{
	DISALLOW_COPY_AND_ASSIGN(ImageToQImage);
private:
	ImageToQImage() = default;
	~ImageToQImage() = default;
public:
	static QImage DoChange( const Image& img );
};
