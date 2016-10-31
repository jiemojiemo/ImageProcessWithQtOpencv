#pragma once

#include "Magic/Magician.h"

class Contourer2 : public Magician
{
	DISALLOW_COPY_AND_ASSIGN(Contourer2);
public:
	Contourer2() = default;
	~Contourer2() = default;

	virtual void DoMagic(MImage& img);
};