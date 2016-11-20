#pragma once
#include "Magic/ImageMeger.h"

class VerticalMerger : public ImageMerger
{
public:
	virtual void InitDstImage();
	virtual void ConstructDstImage();
};