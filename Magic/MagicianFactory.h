#pragma once
#include <map>
#include <string>
#include <memory>
class Magician;
typedef void* (*CreateClass)(void);
class MagicianFactory
{
private:
	MagicianFactory() = default;
public:
	virtual ~MagicianFactory() = default;

	std::unique_ptr<Magician> GetMagicianByName(const std::string& magicianName);
	void RigisterMagician(const std::string& magicianName, CreateClass method);
	static MagicianFactory& SharedMagicianFactory();
private:
	std::map<std::string, CreateClass> m_classMap;
};