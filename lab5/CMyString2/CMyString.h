#pragma once
#include <string>
#include <numeric>
#include <iostream>

class CMyString {
public:
    CMyString();
    CMyString(const char* pString);
    CMyString(const char* pString, size_t length);
    CMyString(CMyString const& other);
    CMyString(CMyString&& other) noexcept;
    CMyString(std::string const& stlString);
    ~CMyString();

    CMyString& operator=(CMyString const& rhs);
    CMyString& operator=(CMyString&& rhs) noexcept;
    CMyString& operator+=(CMyString const& rhs);
    std::strong_ordering operator<=>(CMyString const& rhs) const noexcept;
    const char& operator[](size_t index) const;
    char& operator[](size_t index);

    size_t GetLength() const noexcept;
    size_t GetCapacity() const noexcept;
    [[nodiscard]] const char* GetStringData() const noexcept;

    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
    void Clear() noexcept;

private:
    char* m_chars;
    size_t m_length;
    size_t m_capacity;
};

CMyString operator+(CMyString const& lhs, CMyString const& rhs);
bool operator==(CMyString const& lhs, CMyString const& rhs) noexcept;
std::ostream& operator<<(std::ostream& stream, CMyString const& str);
std::istream& operator>>(std::istream& stream, CMyString& str);