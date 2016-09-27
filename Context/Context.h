#pragma once

#include "common/common.h"
#include <string>

#include <QString>

class Context
{
	DISALLOW_COPY_AND_ASSIGN(Context);
	friend class MRapidJson;
private:
	Context();
private:
	class Impl;
	Impl* m_pImpl;

public:
	static Context& GetContext();
public:
	QString GetCurrentFilename()const;
	void SetCurrentFilename(const QString& filename);
	
	void SetOpenModel(bool isOPen);
	bool IsOpenedImage()const;

	std::string GetMagicanNameFromFunctionName(const std::string& funcName);

public:
	static const int CtxLeftRotateDegree;
	static const int CtxRightRotateDegree;
};
