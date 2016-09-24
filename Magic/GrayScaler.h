#pragma once

#include "Magic\Magician.h"


class GrayScaler : public Magician
{
	DISALLOW_COPY_AND_ASSIGN(GrayScaler);
public:
	GrayScaler() = default;
	virtual ~GrayScaler() = default;

	virtual void DoMagic(Image& img);
};