#pragma once
#include <string>
class DataModel
{
public:
	virtual void SetColVal(int col, const std::string& val) = 0;
};