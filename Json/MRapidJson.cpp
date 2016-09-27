#include "MRapidJson.h"

#include "rapidjson/filereadstream.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include <cassert>
using namespace std;
class MRapidJson::Impl
{
public:
	rapidjson::Document m_doc;
};


auto GetFileSize(FILE* pFile)
{
	fseek(pFile, 0, SEEK_END);
	auto nFileLen = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	return nFileLen;
}

MRapidJson::MRapidJson():m_pImpl(new Impl())
{

}

MRapidJson::~MRapidJson()
{
	if (m_pImpl != nullptr)
	{
		delete m_pImpl;
		m_pImpl = nullptr;
	}
}

void MRapidJson::ReadFile(const std::string& filename)
{
	assert(!filename.empty());

	auto pFile = fopen(filename.c_str(), "r");
	ON_SCOPE_EXIT([&pFile]() {fclose(pFile); });

	if (pFile)
	{
		auto fileSize = GetFileSize(pFile);
		auto buf = new char[fileSize];
		ON_SCOPE_EXIT([&buf]() {delete[] buf; });
		rapidjson::FileReadStream inputStream(pFile, buf, fileSize);
		m_pImpl->m_doc.ParseStream<0>(inputStream);
	}

	if (!m_pImpl->m_doc.IsObject())
	{
		m_pImpl->m_doc.SetObject();
	}
}

void MRapidJson::AddMember(const std::string& key, const std::string& value)
{
	rapidjson::Value strValue(rapidjson::kStringType);
	strValue.SetString(value.c_str(), m_pImpl->m_doc.GetAllocator());
	m_pImpl->m_doc.AddMember(rapidjson::StringRef(key.c_str()), strValue, m_pImpl->m_doc.GetAllocator());
}

bool MRapidJson::HasMember(const std::string& key)
{
	return m_pImpl->m_doc.HasMember(key.c_str());
}

void MRapidJson::RemoveMember(const std::string& key)
{
	if (m_pImpl->m_doc.HasMember(key.c_str()))
		m_pImpl->m_doc.RemoveMember(key.c_str());
}

void MRapidJson::WriteFile(const std::string& filename)
{
	assert(!filename.empty());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer< rapidjson::StringBuffer > writer(buffer);
	m_pImpl->m_doc.Accept(writer);
	const char* str = buffer.GetString();
	FILE * pFile = fopen(filename.c_str(), "w");
	ON_SCOPE_EXIT([&pFile]() {fclose(pFile); });

	if (!pFile) return;
	fwrite(str, sizeof(char), strlen(str), pFile);
}

rapidjson::Document::Object MRapidJson::GetAllObjects()
{
	return m_pImpl->m_doc.GetObject();
}

//rapidjson::Document::ConstObject MRapidJson::GetAllObjects() const
//{
//	return m_pImpl->m_doc.GetObject();
//}
