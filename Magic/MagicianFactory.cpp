#include "Magic/MagicianFactory.h"
#include "Magic/Magician.h"

std::unique_ptr<Magician> MagicianFactory::GetMagicianByName(const std::string& magicianName)
{
	auto iter = m_classMap.find(magicianName);

	if (iter == m_classMap.end())
		return nullptr;
	else
	{
		auto ptr = static_cast<Magician*>(iter->second());
		std::unique_ptr<Magician> ret(ptr);
		return ret;
	}
}

void MagicianFactory::RigisterMagician(const std::string& magicianName, CreateClass method)
{
	m_classMap.insert(std::make_pair(magicianName, method));
}

MagicianFactory& MagicianFactory::SharedMagicianFactory()
{
	static MagicianFactory sharedMagicianFactory;
	return sharedMagicianFactory;
}
