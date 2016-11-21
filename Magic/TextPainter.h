#pragma once
#include "DataStructure/MImage.h"
#include <string>
class TextPainter
{
public:
	virtual QImage PaintText(MImage& img, const std::string& text) = 0;
};