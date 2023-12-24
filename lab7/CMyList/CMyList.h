#pragma once
#include <stdexcept>
#include <string>
#include <iostream>

template <class T>
struct Element
{
    T data;
    Element<T>* next;
    Element<T>* prev;
};

template <class T>
class CMyList
{
public:
    CMyList();
    CMyList(const CMyList& other);
    // Реализовать конструктор перемещения и перемещающий оператор присваивания
    CMyList(CMyList&& other) noexcept;

    CMyList<T>& operator=(const CMyList& other);
    ~CMyList() = default;

    T GetElement(size_t index);

    void AddEnd(T data);
    void AddBegin(T data);
    // void Insert(T data, int index);
    // void Del(int index);
    void Clear();

    bool operator==(const CMyList& obj);

    class CMyListIterator : public std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t>
    {
    public:
        CMyListIterator(int index, CMyList<T>& list, bool isReverse);
        ~CMyListIterator() = default;

        CMyListIterator& operator++();

        bool operator==(const CMyListIterator& other) const;
        bool operator!=(const CMyListIterator& other) const;
        bool operator<(const CMyListIterator& other) const;

        T operator*();
        T operator*() const;

    private:
        CMyList<T>& m_head;
        // указатель на элемент
        int m_index; // Не нужен индекс!!!
        bool m_isReverse;
    };
    // НЕ НУЖЕН ИНДЕКС
    // да это норм что мы не можем добраться резко до конкретного элемента это список)

    CMyListIterator begin();
    CMyListIterator end();

    CMyListIterator rbegin();
    CMyListIterator rend();
    size_t GetSize() const;

private:
    // поля класса с подчёркиванием
    Element<T>* m_lastElement;
    Element<T>* m_firstElement;
    // разобраться зачем указатель на лист?
    // T* m_list; //
    size_t m_size;

    void Copy(const CMyList<T>& obj);

    bool CorrectIndex(int index);

    Element<T>* Move(int index);
};

template <class T>
CMyList<T>::CMyList()
    : m_firstElement(nullptr)
    , m_lastElement(nullptr)
    , m_size(0)
{
    m_firstElement = m_lastElement = nullptr;
}

template <class T>
CMyList<T>::CMyList(const CMyList& other)
        : m_firstElement(nullptr)
        , m_lastElement(nullptr)
        , m_size(0)
{
    Copy(other);
}

//template <class T>
//CMyList<T>::CMyList(CMyList&& other) noexcept
//        : CMyList()
//{
//    Clear();
//    m_list = other.m_list;
//    m_size = other.m_size;
//    other.m_array = nullptr;
//    other.m_size = 0;
//}

template <class T>
CMyList<T>& CMyList<T>::operator=(const CMyList<T>& other)
{
    if (&other == this)
    {
        return *this;
    }// мы ничего не присволил :)
    return *this;
}

template <class T>
void CMyList<T>::AddEnd(T data)
{
    Element<T>* t = new Element<T>;
    t->next = nullptr;
    t->prev = m_lastElement;

    try
    {
        t->data = data; // это T - может выбросить исключение/ и T утечет
    }
    // прочитать про срезку
    catch (const std::bad_alloc* e) // +++ исключение ловят по константной ссылке или по ссылки
    {
        // вывод в cout не обязанность класса
        std::cout << e->what() << std::endl;
        delete t;
        return;
    }

    if (m_lastElement != nullptr)
        m_lastElement->next = t;

    if (m_size == 0)
    {
        m_firstElement = m_lastElement = t;
    }
    else
    {
        m_lastElement = t;
    }

    m_size++;
}

template <class T>
size_t CMyList<T>::GetSize() const
{
    return m_size;
}

template <class T>
void CMyList<T>::Copy(const CMyList<T>& obj)
{
    Clear();
    // + не происходит Строгая гарантия исключений(прежнее\хранить копию)
    try
    {
        Element<T>* t = obj.m_firstElement;

        while (t != nullptr)
        {
            AddEnd(t->data);
            t = t->next;
        }
    }
    catch (const std::bad_alloc* e)
    {
        // вывод в cout не обязанность класса
        std::cout << e->what() << std::endl;

        return;
    }
}

template <class T>
Element<T>* CMyList<T>::Move(int index)
{
    Element<T>* t = m_firstElement;

    for (int i = 0; i < index; i++)
        t = t->next;

    return t;
}

//template <class T>
//void CMyList<T>::Clear()
//{
//    int n = m_size;
//    for (int i = 0; i < n; i++) {
//        Del(0);
//    }
//}

//template <class T>
//void CMyList<T>::Del(int index)
//{
//    if (m_size == 0) return;
//
//    if (!CorrectIndex(index)) // не должно быть, должно работать по итератору
//        return;
//
//    Element<T>* item = Move(index);
//    Element<T>* itemPrev = item->prev;
//    Element<T>* itemNext = item->next;
//
//    if ((m_size > 1) && (itemPrev != nullptr))
//        itemPrev->next = itemNext;
//
//    if ((itemNext != nullptr) && (m_size > 1))
//        itemNext->prev = itemPrev;
//
//    if (index == 0)
//        m_firstElement = itemNext;
//
//    if (index == m_size - 1)
//        m_lastElement = itemPrev;
//
//    delete item;
//    m_size--;
//}

//template <class T>
//void CMyList<T>::Insert(T data, int index)
//{
//
//    if (index == m_size)
//    {
//        AddEnd(data);
//        return;
//    }
//
//    if (!CorrectIndex(index)) {
//        return;
//    }
//
//    if (index == 0)
//    {
//        AddBegin(data);
//        return;
//    }
//
//    try
//    {
//        Element<T>* itemPrev = Move(index - 1);
//        Element<T>* item = Move(index);
//        // добавлять данные в рамках конструктора (оббработается что T создался и не выбросил исключение)
//        auto* t = new Element<T>;
//
//        t->data = data;
//        t->next = item;
//        t->prev = itemPrev;
//        itemPrev->next = t;
//        item->prev = t;
//
//        m_size++;
//    }
//    catch (std::bad_alloc e)
//    {
//        std::cout << e.what() << std::endl;
//    }
//}

template <class T>
T CMyList<T>::GetElement(size_t index)
{
    if (!CorrectIndex(index))
        throw std::out_of_range("Incorrect index.");

    Element<T>* t = Move(index);
    return t->data;
}

template <class T>
bool CMyList<T>::CorrectIndex(int index)
{
    return (index >= 0) && (index < m_size);
}

template <class T>
bool CMyList<T>::operator==(const CMyList<T>& obj)
{
    if (m_size != obj.m_size)
        return false;

    Element<T>* t1 = m_firstElement;
    Element<T>* t2 = obj.m_firstElement;

    while (t1 != nullptr)
    {
        if (t1->data != t2->data)
            return false;

        t1 = t1->next;
        t2 = t2->next;
    }

    return true;
}

// index - не нужно хранить
// можно использовать make_reverce_iterator - котоорая создаёт реверс итератор и можно не делать последний элемент
//template <class T>
//CMyList<T>::CMyListIterator::CMyListIterator(int index, CMyList<T>& list, bool isReverse)
//        : m_index(index)
//        , m_l(list)
//        , m_isReverse(isReverse)
//{
//}

//template <class T>
//typename CMyList<T>::CMyListIterator& CMyList<T>::CMyListIterator::operator++()
//{
//    if (!m_isReverse && *this == m_l.end())
//    {
//        throw std::out_of_range("Incrementing last iterator");
//    }
//    if (m_isReverse && *this == m_l.rend())
//    {
//        throw std::out_of_range("Incrementing last iterator");
//    }
//    !m_isReverse ? m_index++ : m_index--;
//
//    return *this;
//}

template <class T>
bool CMyList<T>::CMyListIterator::operator==(const CMyListIterator& other) const
{
    return m_index == other.m_index;
}

template <class T>
bool CMyList<T>::CMyListIterator::operator!=(const CMyListIterator& other) const
{
    return m_index != other.m_index;
}

template <class T>
bool CMyList<T>::CMyListIterator::operator<(const CMyListIterator& other) const
{
    if (other.m_isReverse != m_isReverse)
    {
        throw std::exception();
    }
    return m_isReverse ? m_index > other.m_index : m_index < other.m_index;
}

//template <class T>
//T CMyList<T>::CMyListIterator::operator*()
//{
//    return m_l.GetElement(size_t(m_index));
//}
// Так же списко должен хранить хотя бы один элемнт - для итератора иначе не воспроизвел end
//template <class T>
//T CMyList<T>::CMyListIterator::operator*() const
//{
//    // итератор - должен хранить указатель на узел, а не его index
//    return m_l.GetElement(size_t(m_index));
//}

template <class T>
typename CMyList<T>::CMyListIterator CMyList<T>::begin()
{
    return CMyList<T>::CMyListIterator(0, *this, false);
}

template <class T>
typename CMyList<T>::CMyListIterator CMyList<T>::end()
{
    return CMyList<T>::CMyListIterator(m_size, *this, false);
}

template <class T>
typename CMyList<T>::CMyListIterator CMyList<T>::rbegin()
{
    return CMyList<T>::CMyListIterator(m_size - 1, *this, true);
}

template <class T>
typename CMyList<T>::CMyListIterator CMyList<T>::rend()
{
    return CMyList<T>::CMyListIterator(-1, *this, true);
}

template <class T>
void CMyList<T>::AddBegin(T data)
{
    try
    {
        Element<T>* t = new Element<T>;
        t->data = data;
        t->prev = nullptr;
        t->next = m_firstElement;

        if (m_size > 0)
        {
            m_firstElement->prev = t;
            m_firstElement = t;
        }
        else
        {
            m_firstElement = m_lastElement = t;
        }

        m_size++;
    }
    catch (std::bad_alloc e)
    {
        std::cout << e.what() << std::endl;
    }
}