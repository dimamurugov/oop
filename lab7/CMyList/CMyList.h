#pragma once
#include <stdexcept>
#include <string>
#include <iostream>
#include <new>
#include <memory>

template <typename T>
struct Node
{
    template <typename TT>
    void Construct(TT&& value)
    {
        std::construct_at(Get(), std::forward<TT>(value));
    }

    void Destroy()
    {
        std::destroy_at(Get());
    }

    T* Get()
    {
        return reinterpret_cast<T*>(raw);
    }

    alignas(T) char raw[sizeof(T)];
};

template <class T>
struct Element
{
    Element<T>* prev;
    Element<T>* next;
    Node<T> data;
};

template <class T>
class CMyList
{
public:
    CMyList();
    CMyList(const CMyList& other);

    ~CMyList() = default;

    class CMyListIterator : public std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t>
    {
    public:
        explicit CMyListIterator(Element<T>* el);

        CMyListIterator& operator++();
        CMyListIterator& operator--();
        CMyListIterator operator--(int);
        bool operator==(CMyListIterator other) const;
        Element<T>* GetNode() const;

        CMyListIterator operator++(int);

        T& operator*() const;

    private:
        Element<T>* m_el;
    };

    bool operator==(const CMyList& obj);
    CMyList& operator=(CMyList const& list);

    void AddEnd(T const& data);
    void AddBegin(T const& data);
    CMyListIterator Insert(CMyListIterator iter, T const& value);
    void Del(CMyListIterator iter);

    CMyListIterator begin();
    CMyListIterator end();

    std::reverse_iterator<CMyListIterator> rbegin();
    std::reverse_iterator<CMyListIterator> rend();
    size_t GetSize() const;

private:
    Element<T>* m_Sentinel;
    Element<T>* m_firstElement;
    size_t m_size;

    void Copy(const CMyList<T>& obj);
};

template <class T>
CMyList<T>::CMyList()
    : m_Sentinel()
    , m_firstElement()
    , m_size(0)
{
    m_Sentinel = new Element<T>{ m_Sentinel, m_Sentinel };
    m_firstElement = m_Sentinel;
}

template <class T>
CMyList<T>::CMyList(const CMyList& other)
    : m_Sentinel()
    , m_firstElement()
    , m_size(0)
{
    m_Sentinel = new Element<T>{ m_Sentinel, m_Sentinel };
    m_firstElement = m_Sentinel;

    Copy(other);
}

template <class T>
void CMyList<T>::AddEnd(T const& data)
{
    if (m_size == 0)
    {
        AddBegin(data);
        return;
    }

    auto* t = new Element<T>;
    t->prev = m_Sentinel->prev;
    t->next = m_Sentinel;
    t->data.Construct(data);

    m_Sentinel->prev->next = t;
    m_Sentinel->prev = t;

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
    Element<T>* t = obj.m_firstElement;
    auto size = obj.GetSize();

    for (int i = 0; i < size; ++i) {
        AddEnd(*(t->data.Get()));
        t = t->next;
    }
}

template <class T>
void CMyList<T>::Del(CMyListIterator iter)
{
    if (m_size == 0) return;

    Element<T>* node = iter.GetNode();
    Element<T>* nextNode = node->next;
    Element<T>* prevNode = node->prev;

    if (prevNode != nullptr)
    {
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }
    else
    {
        m_firstElement = nextNode;
        nextNode->prev = nullptr;
    }

    node->data.Destroy();
    delete node;
    m_size--;
}

template <class T>
typename CMyList<T>::CMyListIterator CMyList<T>::Insert(CMyListIterator iter, T const& value)
{
    if (iter == end())
    {
        AddEnd(value);
        return --end();
    }
    if (iter == begin())
    {
        AddBegin(value);
        return begin();
    }
    Element<T>* node = iter.GetNode();
    Element<T>* newNode = new Element<T>;
    newNode->prev = node->prev;
    newNode->next = node;
    newNode->data.Construct(value);
    node->prev->next = newNode;
    node->prev = newNode;
    m_size++;

    return CMyList<T>::CMyListIterator(newNode);
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

template <class T>
CMyList<T>::CMyListIterator::CMyListIterator(Element<T>* el)
        : m_el(el)
{}

template<class T>
typename CMyList<T>::CMyListIterator &CMyList<T>::CMyListIterator::operator--() {
    m_el = m_el->prev;
    return *this;
}

template <class T>
typename CMyList<T>::CMyListIterator& CMyList<T>::CMyListIterator::operator++()
{
    m_el = m_el->next;
    return *this;
}

template <class T>
T& CMyList<T>::CMyListIterator::operator*() const
{
    return *m_el->data.Get();
}

template<class T>
Element<T> *CMyList<T>::CMyListIterator::GetNode() const {
    return m_el;
}

template<class T>
bool CMyList<T>::CMyListIterator::operator==(CMyList::CMyListIterator other) const {
    return m_el == other.m_el;
}

template<class T>
typename CMyList<T>::CMyListIterator CMyList<T>::CMyListIterator::operator--(int) {
    CMyListIterator retval = *this;
    --(*this);
    return retval;
}

template<class T>
typename CMyList<T>::CMyListIterator CMyList<T>::CMyListIterator::operator++(int) {
    CMyListIterator retval = *this;
    ++(*this);
    return retval;
}

template <class T>
typename CMyList<T>::CMyListIterator CMyList<T>::begin()
{
    return CMyList<T>::CMyListIterator(m_firstElement);
}

template <class T>
typename CMyList<T>::CMyListIterator CMyList<T>::end()
{
    return CMyList<T>::CMyListIterator(m_Sentinel);
}

template <class T>
std::reverse_iterator<typename CMyList<T>::CMyListIterator> CMyList<T>::rbegin()
{
    return std::reverse_iterator<CMyListIterator>(end());
}

template <class T>
std::reverse_iterator<typename CMyList<T>::CMyListIterator> CMyList<T>::rend()
{
    return std::reverse_iterator<CMyListIterator>(begin());
}

template <class T>
void CMyList<T>::AddBegin(T const& data)
{
    Element<T>* t = new Element<T>;
    t->prev = nullptr;
    t->next = m_firstElement;
    t->data.Construct(data);

    m_firstElement = t;
    m_firstElement->next->prev = m_firstElement;

    m_size++;
}

template<class T>
CMyList<T> &CMyList<T>::operator=(const CMyList &list) {
    if (&list != this) {
        CMyList Copy(list);
    }

    return *this;
}
