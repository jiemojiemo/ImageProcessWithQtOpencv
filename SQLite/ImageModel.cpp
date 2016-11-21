#include "SQLite/ImageModel.h"
#include <sstream>
void ImageModel::SetColVal(int col, const std::string& val)
{
	switch (col)
	{
	case 0:SetString(URL, val); break;
	case 1:SetString(name, val); break;
	case 2:SetInt(width, val); break;
	case 3:SetInt(height, val); break;
	case 4:SetInt(size, val); break;
	default:
		break;
	}
}

void ImageModel::SetString(std::string& str, const std::string& val)
{
	str = val;
}

void ImageModel::SetInt(int& i, const std::string& val)
{
	if (val == "NULL")
	{
		i = 0;
		return;
	}

	std::stringstream ss(val);
	int v = 0;
	ss >> v;
	i = v;
}

