#pragma once
#include "common/common.h"
#include "Magic/MagicianFactory.h"

#include <string>
class MagicianRegister
{
	DISALLOW_COPY_AND_ASSIGN(MagicianRegister);
public:
	MagicianRegister(const std::string& magicianName, CreateClass method)
	{
		MagicianFactory::SharedMagicianFactory().RigisterMagician(magicianName, method);
	}
};

