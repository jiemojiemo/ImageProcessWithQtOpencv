#pragma once
#include "Magic/TextPainter.h"

class TextPainterImpl : public TextPainter
{
public:
	virtual QImage PaintText(MImage& img, const std::string& text);
};
