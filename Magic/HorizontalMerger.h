#pragma once
#include "Magic/ImageMeger.h"

class HorizontalMerger : public ImageMerger
{
public:
	virtual void InitDstImage();
	virtual void ConstructDstImage();
};
