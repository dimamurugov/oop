#include "CMyString.h"
#include <stdexcept>
#include <vector>
#include <cstring>

CMyString::CMyString()
        : m_chars(new char[1])
        , m_length(0)
        , m_capacity(1)
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
        , m_capacity(length * 2)
{
    std::copy(pString, pString + length, m_chars);
    m_chars[m_length] = '\0';
}

CMyString::CMyString(char* pString, size_t length, int)
        : m_chars(pString)
        , m_length(length)
        , m_capacity(length * 2)
{
}

CMyString::CMyString(std::string const& stlString)
        : CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::CMyString(CMyString&& other) noexcept
        : m_chars(other.m_chars)
        , m_length(other.m_length)
        , m_capacity(other.m_length * 2)
{
    other.m_chars = nullptr;
    other.m_length = 0;
    other.m_capacity = 0;
}

CMyString::~CMyString()
{
    delete[] m_chars;
}

size_t CMyString::GetLength() const noexcept
{
    return m_length;
}

size_t CMyString::GetCapacity() const noexcept
{
    return m_capacity;
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

CMyString& CMyString::operator+=(CMyString const& rhs)
{
    size_t otherLength = rhs.GetLength();
    if (m_capacity <= m_length + otherLength)
    {
        *this = *this + rhs;
        return *this;
    }

    std::copy(rhs.GetStringData(), rhs.GetStringData() + rhs.GetLength(), m_chars + m_length);
    m_length += otherLength;
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

    return CMyString(m_chars + start, std::min(m_length - start, length));
}

void CMyString::Clear() noexcept
{
    delete[] m_chars;
    m_length = 0;
    m_chars = nullptr;
}

CMyString operator+(CMyString const& lhs, CMyString const& rhs)
{
    if (lhs.GetLength() >= SIZE_MAX - rhs.GetLength())
    {
        throw std::length_error("String cannot be longer than SIZE_MAX");
    }

    size_t length = lhs.GetLength() + rhs.GetLength();
    char* chars = new char[length * 2];
    std::copy(lhs.GetStringData(), lhs.GetStringData() + lhs.GetLength(), chars);
    std::copy(rhs.GetStringData(), rhs.GetStringData() + rhs.GetLength(), chars + lhs.GetLength());
    chars[length] = '\0';

    return CMyString(chars, length, int{});
}

bool operator==(CMyString const& lhs, CMyString const& rhs) noexcept
{
    if (lhs.GetLength() != rhs.GetLength())
    {
        return false;
    }
    auto lArr = lhs.GetStringData();
    auto rArr = rhs.GetStringData();

    return std::equal(lArr, lArr + lhs.GetLength(), rArr);
}

const char& CMyString::operator[](size_t index) const
{
    if (index >= m_length)
    {
        throw std::out_of_range("Index out of range");
    }
    return m_chars[index];
}

char& CMyString::operator[](size_t index)
{
    if (index >= m_length)
    {
        throw std::out_of_range("Index out of range");
    }
    return m_chars[index];
}

std::strong_ordering CMyString::operator<=>(CMyString const& rhs) const noexcept
{
    auto lArr = GetStringData();
    auto rArr = rhs.GetStringData();

    return std::lexicographical_compare_three_way(lArr, lArr + m_length, rArr, rArr + rhs.m_length);
}

std::ostream& operator<<(std::ostream& stream, CMyString const& str)
{
    for (size_t i = 0; i < str.GetLength(); i++)
    {
        stream << str[i];
    }
    return stream;
}

std::istream& operator>>(std::istream& stream, CMyString& str)
{
    std::vector<char> chars;
    char ch;
    while (stream.get(ch) && ch != ' ' && chars.size() < SIZE_MAX)
    {
        chars.push_back(ch);
    }

    char* copyChars = new char[chars.size() + 1];
    std::copy(chars.begin(), chars.end(), copyChars);
    copyChars[chars.size()] = '\0';
    str = std::move(copyChars);
    delete[] copyChars;

    return stream;
}