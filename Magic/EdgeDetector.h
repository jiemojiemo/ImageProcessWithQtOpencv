#pragma once

#include "Magic/Magician.h"

class EdgeDetector : public Magician
{
	DISALLOW_COPY_AND_ASSIGN(EdgeDetector);
public:
	EdgeDetector() = default;
	virtual ~EdgeDetector() = default;

	virtual void DoMagic(MImage& img);
};


