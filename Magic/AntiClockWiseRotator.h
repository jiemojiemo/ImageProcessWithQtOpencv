#pragma once
#include "Magic/Magician.h"

class AntiClockWiseRotator : public Magician
{
public:
	AntiClockWiseRotator() = default;

	virtual ~AntiClockWiseRotator() = default;

	virtual void DoMagic(Image& img);
};