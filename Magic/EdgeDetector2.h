#pragma once						

#include "Magic/Magician.h"

class EdgeDetector2 : public Magician
{
	DISALLOW_COPY_AND_ASSIGN(EdgeDetector2);
public:
	EdgeDetector2() = default;
	~EdgeDetector2() = default;

	virtual void DoMagic(MImage& img);
};
