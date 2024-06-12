#include "CMyString.h"
#include <stdexcept>
#include <vector>
#include <cstring>

CMyString::CMyString()
        : m_chars(new char[1])
        , m_length(0)
{
    m_chars[0] = '\0';
}

CMyString::CMyString(const char* pString)
        : CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(CMyString const& other)
        : CMyString(other.GetStringData(), other.GetLength())
{
}

CMyString::CMyString(const char* pString, size_t length)
        : m_chars(new char[length + 1])
        , m_length(length)
{
    std::copy(pString, pString + length, m_chars);
    m_chars[m_length] = '\0';
}

//CMyString::CMyString(char* pString, size_t length, int)
//        : m_chars(pString)
//        , m_length(length)
//{
//}

CMyString::CMyString(std::string const& stlString)
        : CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::CMyString(CMyString&& other) noexcept
        : m_chars(other.m_chars)
        , m_length(other.m_length)
{
    other.m_chars = nullptr;
    other.m_length = 0;
}

CMyString::~CMyString()
{
    delete[] m_chars;
}

size_t CMyString::GetLength() const noexcept
{
    return m_length;
}

CMyString& CMyString::operator=(CMyString const& rhs)
{
    if (&rhs != this)
    {
        CMyString copyStr(rhs);
        std::swap(m_chars, copyStr.m_chars);
        std::swap(m_length, copyStr.m_length);
    }

    return *this;
}

CMyString& CMyString::operator=(CMyString&& rhs) noexcept
{
    if (&rhs != this)
    {
        delete[] m_chars;
        m_length = rhs.GetLength();
        m_chars = rhs.m_chars;
        rhs.m_chars = nullptr;
        rhs.m_length = 0;
    }
    return *this;
}
char zeroCode[1] = { '\0' };
const char* CMyString::GetStringData() const noexcept
{
    if (m_chars == nullptr)
    {
        return zeroCode;
    }
    return m_chars;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
    if (start >= m_length)
    {
        throw std::out_of_range("Start index of substring can not be greater than string length");
    }

    return {m_chars + start, std::min(m_length - start, length)};
}

void CMyString::Clear() noexcept
{
    delete[] m_chars;
    m_length = 0;
    m_chars = nullptr;
}
