#include "Context/Context.h"

Context::Context():
	m_isOpenedImage(false)
{

}

Context& Context::GetContext()
{
	static Context context;
	return context;
}