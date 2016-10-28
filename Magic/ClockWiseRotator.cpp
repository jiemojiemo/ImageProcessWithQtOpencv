#include "Magic/ClockWiseRotator.h"
#include "DataStructure/Image.h"

#include "ImageRotator/QImageRotator.h"
#include "Context/Context.h"

REGISTER_INTO_FACTORY(ClockWiseRotator);

void ClockWiseRotator::DoMagic(Image& img)
{
	QImageRotator rotate;
	rotate.Rotate(img.GetQImage(), Context::CtxRightRotateDegree);
}
