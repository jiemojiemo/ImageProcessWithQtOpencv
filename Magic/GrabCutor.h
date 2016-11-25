#pragma once
#include "Magic/Magician.h"

class GrabCutor : public Magician
{
	DISALLOW_COPY_AND_ASSIGN(GrabCutor);
public:
	GrabCutor() = default;
	~GrabCutor() = default;

	virtual void DoMagic(MImage& img);
};
