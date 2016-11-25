#pragma once
#include "Magic/Magician.h"

#include <memory>

class Image
{
public:
	Image() :m_mag(nullptr) {}

	virtual void DoMagic() = 0;
	virtual void SetMag(std::shared_ptr<Magician>& val) = 0;

protected:
	std::shared_ptr<Magician> m_mag;
};
