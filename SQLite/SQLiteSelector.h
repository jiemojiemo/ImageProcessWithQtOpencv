#pragma once

#include "SQLite/SQLSelector.h"
#include "SQLite/sqlite3.h"
#include <strstream>
#include <vector>

template <typename T>
class SQLiteSelector : public SQLSelector<T>
{
public:
	SQLiteSelector(const std::string& dbPath);
	virtual std::vector<T> SelectAll(const std::string& tableName);
	virtual ~SQLiteSelector();

private:
	static int Callback(void *NotUsed, int argc, char **argv, char **azColName);
protected:
	sqlite3* m_pDB;
	static std::vector<T> m_selectResult;
};
template<typename T>
std::vector<T> SQLiteSelector<T>::m_selectResult;

template <typename T>
int SQLiteSelector<T>::Callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	T temp;
	for (int i = 0; i < argc; ++i)
	{
		temp.SetColVal(i, (argv[i] ? argv[i] : "NULL"));
	}
	m_selectResult.push_back(temp);
	return 0;
}


template <typename T>
std::vector<T> SQLiteSelector<T>::SelectAll(const std::string& tableName)
{
	char* errMsg;
	std::string strSQL= "select * from " + tableName + ";";

	m_selectResult.clear();
	
	sqlite3_exec(m_pDB, strSQL.c_str(), Callback, 0, &errMsg);
	return m_selectResult;
}

template <typename T>
SQLiteSelector<T>::SQLiteSelector(const std::string& dbPath):SQLSelector(dbPath)
{
	int res = sqlite3_open(dbPath.c_str(), &m_pDB);
	if (res)
	{
		sqlite3_close(m_pDB);
		m_pDB = nullptr;
	}
}

template <typename T>
SQLiteSelector<T>::~SQLiteSelector()
{
	if (m_pDB != nullptr)
	{
		sqlite3_close(m_pDB);
		m_pDB = nullptr;
	}
}