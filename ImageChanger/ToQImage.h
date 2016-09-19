#pragma once

#include "common/common.h"

class Image;
class QImage;

class ToQImage
{
	DISALLOW_COPY_AND_ASSIGN(ToQImage);
private:
	ToQImage() = default;
	~ToQImage() = default;
public:
	static QImage DoChange( const Image& img, QImage& qImg );
};
