#pragma once

#include "Magic\Magician.h"


class Carver : public Magician
{
	DISALLOW_COPY_AND_ASSIGN(Carver);
public:
	Carver() = default;
	virtual ~Carver() = default;

	virtual void DoMagic(MImage& img);
};