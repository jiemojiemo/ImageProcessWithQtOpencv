#pragma once
#include "Magic/QTextPainter.h"

class VerticalTextPainterImpl : public QTextPainter
{
public:
	virtual QImage PaintText(MImage& img, const std::string& text);
};
#pragma once
