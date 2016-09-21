#pragma once

#include "common/common.h"
#include <QString>

class Context
{
	DISALLOW_COPY_AND_ASSIGN(Context);
private:
	Context();
private:
	QString m_currentFilename;
	bool m_isOpenedImage;
public:
	static Context& GetContext();
public:
	QString GetCurrentFilename()const { return m_currentFilename; }
	void SetCurrentFilename(const QString& filename) { m_currentFilename = filename; }
	
	bool SetOpenModel(bool isOPen) { m_isOpenedImage = isOPen; }
	bool IsOpenedImage()const { return m_isOpenedImage; }

public:
	static const int CtxLeftRotateDegree;
	static const int CtxRightRotateDegree;
};
