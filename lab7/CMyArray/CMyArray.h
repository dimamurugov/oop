#pragma once
#include <initializer_list>
#include <iterator>
#include <stdexcept>

template <class T>
class CMyArray
{
public:
    CMyArray();
    CMyArray(const CMyArray& other);
    CMyArray(const std::initializer_list<T>& list);
    CMyArray(CMyArray&& other) noexcept;
    ~CMyArray();

    class CMyArrayIterator : public std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t>
    {
    public:
        CMyArrayIterator(int index, CMyArray<T>& array, bool isReverse);
        ~CMyArrayIterator() = default;

        CMyArrayIterator& operator++();
        CMyArrayIterator& operator--();

        bool operator==(const CMyArrayIterator& other) const;
        bool operator!=(const CMyArrayIterator& other) const;
        bool operator<(const CMyArrayIterator& other) const;

        T& operator*();
        const T& operator*() const;

    private:
        int m_pos;
        CMyArray<T>& m_arr;
        bool m_isReverse;
    };

    CMyArray<T>& operator=(CMyArray<T>&& other) noexcept;
    CMyArray<T>& operator=(const CMyArray<T>& other);

    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;

    CMyArrayIterator begin();
    CMyArrayIterator end();

    CMyArrayIterator rbegin();
    CMyArrayIterator rend();

    void PushBack(T element);
    void Clear();
    void Resize(size_t newSize);
    size_t Size() const;

private:
    T* m_array;
    size_t m_size;
    // ещё capacyty - должна быть вместимость, а не только размер
};
