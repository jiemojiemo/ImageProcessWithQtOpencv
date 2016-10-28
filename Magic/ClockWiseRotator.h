#pragma once
#include "Magic/Magician.h"

class ClockWiseRotator : public Magician
{
public:
	ClockWiseRotator() = default;

	virtual ~ClockWiseRotator() = default;

	virtual void DoMagic(Image& img);
};