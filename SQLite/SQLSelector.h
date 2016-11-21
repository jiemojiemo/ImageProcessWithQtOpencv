#pragma once
#include <vector>
#include <string>

template<typename T>
class SQLSelector
{
public:
	SQLSelector(const std::string& dbPath) :m_dbPath(dbPath) {}

	virtual std::vector<T> SelectAll(const std::string& tableName) = 0;
	virtual ~SQLSelector()=default;

	std::string GetDBPath()const { return m_dbPath; }

protected:
	std::string m_dbPath;
};