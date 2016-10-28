#pragma once

#include "FileOperator/ImageFileOperator.h"

class QImageFileOperator : public ImageFileOperator
{
	DISALLOW_COPY_AND_ASSIGN(QImageFileOperator);
public:
	QImageFileOperator() = default;
	~QImageFileOperator() = default;

	virtual std::string Open();
	virtual bool Save( const Image& img, const std::string& filename);
	virtual bool SaveAs( const Image& img);
};
