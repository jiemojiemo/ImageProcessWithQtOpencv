#pragma once
#include <memory>
#include "rapidjson/document.h"
#include "Json/MagicJson.h"

class MRapidJson : public MagicJson
{
	DISALLOW_COPY_AND_ASSIGN(MRapidJson);
public:
	friend class Context;
	MRapidJson();
	virtual ~MRapidJson();

public:
	virtual void ReadFile(const std::string& filename);
	virtual void AddMember(const std::string& key, const std::string& value);
	virtual bool HasMember(const std::string& key);
	virtual void RemoveMember(const std::string& key);
	virtual void WriteFile(const std::string& filename);

	rapidjson::Document::Object GetAllObjects();
	//rapidjson::Document::ConstObject GetAllObjects() const;

private:
	class Impl;
	Impl* m_pImpl;
};
