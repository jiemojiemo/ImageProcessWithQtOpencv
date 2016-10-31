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
	virtual ~OilPainter() = default;

	virtual void DoMagic(MImage& img);
};