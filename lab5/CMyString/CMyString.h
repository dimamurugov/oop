#pragma once
#include <string>
#include <numeric>
#include <iostream>

class CMyString {
public:
    CMyString();
    CMyString(const char* pString); // строку с завершающим нулевым символом
    CMyString(const char* pString, size_t length); // строку данными из символьного массива заданной длины
    CMyString(CMyString const& other);
    CMyString(CMyString&& other) noexcept;
    CMyString(std::string const& stlString); // строку данными из строки стандартной библиотеки C++
    ~CMyString();

    CMyString& operator=(CMyString const& rhs);
    CMyString& operator=(CMyString&& rhs) noexcept;

    size_t GetLength() const noexcept;
    [[nodiscard]] const char* GetStringData() const noexcept;

    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
    void Clear() noexcept;
    size_t GetCapacity();

//private:
//  CMyString(char* pString, size_t length, int); // это вот зачем?

private:
    char* m_chars;
    size_t m_length;
};
