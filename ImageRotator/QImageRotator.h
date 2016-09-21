#pragma once

#include "common/common.h"

class QImage;

class QImageRotator
{
	DISALLOW_COPY_AND_ASSIGN(QImageRotator);
public:
	QImageRotator() = default;
	~QImageRotator() = default;

	QImage Rotate(QImage& qImg, int degree);
	QImage GetRotateQImage(const QImage& qImg, int degree);
};