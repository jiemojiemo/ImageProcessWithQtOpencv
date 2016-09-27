#include "Context/Context.h"
#include "Json/MRapidJson.h"
#include "Magic/MagicianRegister.h"

#include <cassert>
#include <map>

using namespace std;

const int Context::CtxLeftRotateDegree = 90;
const int Context::CtxRightRotateDegree = -90;



class Context::Impl
{
	DISALLOW_COPY_AND_ASSIGN(Impl);
public:
	Impl() = default;
	~Impl() = default;
	void LoadJson(const string& jsonanem);
public:
	QString m_currentFilename;
	bool m_isOpenedImage;
	map<string, string> m_funcMap;
};

void Context::Impl::LoadJson(const string& jsonanem)
{
	MRapidJson json;
	json.ReadFile(jsonanem);
	for (auto& it : json.GetAllObjects())
	{
		string funcName = it.name.GetString();
		string magicianName = it.value.GetString();
		m_funcMap.insert(make_pair(funcName, magicianName));
	}
}


Context::Context() :m_pImpl(new Impl())
{
	m_pImpl->m_isOpenedImage = false;
	m_pImpl->m_currentFilename = "";

	m_pImpl->LoadJson("app.json");
}

Context& Context::GetContext()
{
	static Context context;
	return context;
}

QString Context::GetCurrentFilename() const
{
	return m_pImpl->m_currentFilename;
}

void Context::SetCurrentFilename(const QString& filename)
{
	assert(!filename.isEmpty());
	m_pImpl->m_currentFilename = filename;
}

void Context::SetOpenModel(bool isOPen)
{
	m_pImpl->m_isOpenedImage = isOPen;
}

bool Context::IsOpenedImage() const
{
	return m_pImpl->m_isOpenedImage;
}

std::string Context::GetMagicanNameFromFunctionName(const std::string& funcName)
{
	auto iter = m_pImpl->m_funcMap.find(funcName);
	if (iter != m_pImpl->m_funcMap.end())
	{
		return iter->second;
	}
	return string();
}
