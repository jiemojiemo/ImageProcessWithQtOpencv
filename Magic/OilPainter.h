#pragma once
#include "Magic/Magician.h"

/*
	NOTE:Only RGB image can be oiled
*/
class OilPainter
{
	DISALLOW_COPY_AND_ASSIGN(OilPainter);

public:
	OilPainter() = default;
	~OilPainter() = default;

	virtual void DoMagic(Image& img);
};