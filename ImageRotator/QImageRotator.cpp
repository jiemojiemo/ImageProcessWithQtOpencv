#include "ImageRotator/QImageRotator.h"
#include <QImage>
#include <QMatrix>

QMatrix GetRotateMatrix(int degree)
{
	QMatrix rotateMatrix;

	rotateMatrix.rotate(degree);

	return rotateMatrix;
}


QImage QImageRotator::Rotate(QImage& qImg, int degree)
{
	qImg = GetRotateQImage(qImg, degree);
	return qImg;
}

QImage QImageRotator::GetRotateQImage(const QImage& qImg, int degree)
{
	auto rotateMatrix = GetRotateMatrix(degree);
	return qImg.transformed(rotateMatrix);
}

