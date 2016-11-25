#pragma once
#include "Magic/Magician.h"

class Stretchor : public Magician
{
	DISALLOW_COPY_AND_ASSIGN(Stretchor);
public:
	Stretchor() = default;
	~Stretchor() = default;

	virtual void DoMagic(MImage& img);
};

