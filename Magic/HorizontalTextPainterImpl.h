#pragma once
#include "Magic/QTextPainter.h"

class HorizontalTextPainterImpl : public QTextPainter
{
public:
	virtual QImage PaintText(MImage& img, const std::string& text);
};
