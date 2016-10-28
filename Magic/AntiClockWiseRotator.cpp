#include "Magic/AntiClockWiseRotator.h"
#include "DataStructure/Image.h"

#include "ImageRotator/QImageRotator.h"
#include "Context/Context.h"


REGISTER_INTO_FACTORY(AntiClockWiseRotator);

void AntiClockWiseRotator::DoMagic(Image& img)
{
	QImageRotator rotate;
	rotate.Rotate(img.GetQImage(), Context::CtxLeftRotateDegree);
}
