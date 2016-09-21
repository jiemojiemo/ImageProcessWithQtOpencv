#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "common/common.h"


class Image;
class Magician
{
	DISALLOW_COPY_AND_ASSIGN(Magician);
public:
	Magician() = default;
	~Magician() = default;

	virtual void DoMagic(Image& img) = 0;

};

#endif // MAGIC_H
