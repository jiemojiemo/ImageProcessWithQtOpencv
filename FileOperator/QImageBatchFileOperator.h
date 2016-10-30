#pragma once
#include "FileOperator/QImageFileOperator.h"
#include <list>
class QImageBatchFileOperator : public QImageFileOperator
{
public:
	QImageBatchFileOperator() = default;
	virtual ~QImageBatchFileOperator() = default;

	std::list<std::string> OpenFolder();
	
};