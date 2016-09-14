#pragma once

#include "Magic/Magician.h"

class EdgeDetector : public Magician
{
	DISALLOW_COPY_AND_ASSIGN(EdgeDetector);
	friend class Image;
public:
	EdgeDetector() = default;
	~EdgeDetector() = default;

	virtual void DoMagic(Image& img);
};
