#pragma once
#include "common/common.h"
#include <string>
class MagicJson
{
	DISALLOW_COPY_AND_ASSIGN(MagicJson);
public:
	MagicJson() = default;
	virtual ~MagicJson() = default;

public:
	virtual void ReadFile(const std::string& filename) = 0;
	virtual void AddMember(const std::string& key, const std::string& value) = 0;
	virtual bool HasMember(const std::string& key) = 0;
	virtual void RemoveMember(const std::string& key) = 0;
	virtual void WriteFile(const std::string& filename) = 0;
};
