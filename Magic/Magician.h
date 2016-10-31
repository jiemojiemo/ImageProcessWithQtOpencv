#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "common/common.h"
#include "Magic/MagicianRegister.h"

class MImage;
class Magician
{
	DISALLOW_COPY_AND_ASSIGN(Magician);
public:
	Magician() = default;
	virtual ~Magician() = default;

	virtual void DoMagic(MImage& img) = 0;

};
//#define REGISTER_CAT(className) className##Factoory
//#define REGISTER_CLASS_NAME REGISTER_CAT(className)

#define REGISTER_INTO_FACTORY(className)				\
class className##Register					\
{														\
public:													\
	className##Register()=default;				\
	static void* GetInstance(){return new className();}\
private:												\
	static const MagicianRegister m_register;			\
};														\
const MagicianRegister className##Register::m_register(#className,GetInstance)

#endif // MAGIC_H
