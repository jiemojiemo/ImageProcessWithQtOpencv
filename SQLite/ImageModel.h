#pragma once
#include "SQLite/DataModel.h"
#include <string>
class ImageModel : public DataModel
{
public:
	std::string GetURL() const { return URL; }
	void SetURL(std::string val) { URL = val; }
	std::string GetName() const { return name; }
	void SetName(std::string val) { name = val; }
	int GetWidth() const { return width; }
	void SetWidth(int val) { width = val; }
	int GetHeight() const { return height; }
	void SetHeight(int val) { height = val; }
	int GetSize() const { return size; }
	void SetSize(int val) { size = val; }

	std::string GetFullPath() { return URL + "\\" + name; }

	virtual void SetColVal(int col, const std::string& val);
private:
	void SetString(std::string& str, const std::string& val);
	void SetInt(int& i, const std::string& val);
private:
	std::string URL;
	std::string name;
	int width;
	int height;
	int size;
};