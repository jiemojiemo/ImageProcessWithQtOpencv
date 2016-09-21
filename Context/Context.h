#pragma once

#include "common/common.h"
#include <string>

class Context
{
	DISALLOW_COPY_AND_ASSIGN(Context);
private:
	Context();
private:
	std::string m_currentFilename;
	bool m_isOpenedImage;
public:
	static Context& GetContext();
public:
	std::string GetCurrentFilename()const { return m_currentFilename; }
	void SetCurrentFilename(const std::string& filename) { m_currentFilename = filename; }
	
	bool SetOpenModel(bool isOPen) { m_isOpenedImage = isOPen; }
	bool IsOpenedImage()const { return m_isOpenedImage; }
};
