#pragma once

#include "Magic\Magician.h"


class Embosser : public Magician
{
	DISALLOW_COPY_AND_ASSIGN(Embosser);
public:
	Embosser() = default;
	virtual ~Embosser() = default;

	virtual void DoMagic(MImage& img);
};