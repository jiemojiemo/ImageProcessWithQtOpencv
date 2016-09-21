#include "Context/Context.h"

const int Context::CtxLeftRotateDegree = 90;
const int Context::CtxRightRotateDegree = -90;

Context::Context() :m_isOpenedImage(false)
{

}

Context& Context::GetContext()
{
	static Context context;
	return context;
}