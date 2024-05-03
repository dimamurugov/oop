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
        // что будет если здесь будет ошибка (для всех мест)
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
    Node<T> current;
    bool isEmpty;
};

template <class T>
class CMyList
{
public:
    CMyList();
    CMyList(const CMyList& other);
    // конструктор перемещения
    // перемещающий оператор присваивания

    ~CMyList() = default;
    // Есть указатель, нужен деструктор пользовательский деструктор

    class CMyListIterator : public std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t>
    {
    public:
        explicit CMyListIterator(Element<T>* el);
        // Константный итератор нужен ещё

        CMyListIterator& operator++();
        CMyListIterator operator++(int);

        CMyListIterator& operator--();

        CMyListIterator operator--(int);

        bool operator==(CMyListIterator other) const;
        Element<T>* GetNode() const;

        T& operator*() const;

    private:
        Element<T>* m_el;
    };

    bool operator==(const CMyList& obj);
    CMyList& operator=(CMyList const& list);

    void AddEnd(T const& current);
    void AddBegin(T const& current);
    CMyListIterator Insert(CMyListIterator iter, T const& value);
    void Del(CMyListIterator iter);

    CMyListIterator begin();
    CMyListIterator end();

    std::reverse_iterator<CMyListIterator> rbegin();
    std::reverse_iterator<CMyListIterator> rend();
    [[nodiscard]] size_t GetSize() const;

private:
    Element<T>* m_sentinel;
    Element<T>* m_firstElement;
    size_t m_size;

    void Copy(const CMyList<T>& obj);
};

template <class T>
CMyList<T>::CMyList()
    : m_sentinel()
    , m_firstElement()
    , m_size(0)
{
    m_sentinel = new Element<T>;
    m_sentinel->next = m_sentinel;
    m_sentinel->prev = m_sentinel;
    m_sentinel->isEmpty = true;
    m_firstElement = m_sentinel;
}

template <class T>
CMyList<T>::CMyList(const CMyList& other)
    : m_sentinel()
    , m_firstElement()
    , m_size(0)
{
    m_sentinel = new Element<T>;
    m_sentinel->next = m_sentinel;
    m_sentinel->prev = m_sentinel;
    m_sentinel->isEmpty = true;
    m_firstElement = m_sentinel;

    Copy(other);
}

template <class T>
void CMyList<T>::AddEnd(T const& current)
{
    if (m_size == 0)
    {
        AddBegin(current);
        return;
    }

    auto* newElement = new Element<T>;

    try {
        newElement->current.Construct(current);
    }
    catch (const std::exception& ex) {
        throw ex;
    }

    newElement->prev = m_sentinel->prev;
    newElement->next = m_sentinel;
    newElement->isEmpty = false;
    m_sentinel->prev->next = newElement;
    m_sentinel->prev = newElement;

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
        AddEnd(*(t->current.Get()));
        t = t->next;
    }
}

template <class T>
void CMyList<T>::Del(CMyListIterator iter)
{
    if (m_size == 0) throw std::out_of_range("empty list");
    if (iter.GetNode() == m_sentinel) throw std::out_of_range("out of range");
    // если сюда передать стража TODO сверху добавил проверку
    Element<T>* node = iter.GetNode();
    Element<T>* nextNode = node->next;
    Element<T>* prevNode = node->prev;

    if (node == m_firstElement)
    {
        m_firstElement = nextNode;
        nextNode->prev = m_sentinel;
    }
    else
    {
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    node->current.Destroy();
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
    auto* newElement = new Element<T>;
    try {
        newElement->current.Construct(value);
    }
    catch (const std::exception& ex) {
        throw ex;
    }

    newElement->prev = node->prev;
    newElement->next = node;
    newElement->isEmpty = false;

    node->prev->next = newElement;
    node->prev = newElement;
    m_size++;

    return CMyList<T>::CMyListIterator(newElement);
}

template <class T>
bool CMyList<T>::operator==(const CMyList<T>& obj)
{
    if (m_size != obj.m_size) return false;

    Element<T>* t1 = m_firstElement;
    Element<T>* t2 = obj.m_firstElement;

    while (t1 != m_sentinel) // тут тоже переделать на проверку первого элемента TODO достаточно m_sentinel
    {
        if (t1->current != t2->current)
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
    // выкидывать ошибку, что мы вышли за пределы списка (если скинул первый элемент)
    // у стража - по сути нет даты (есть сырая память)
    // TODO я гарантирую что список останется в валидном состоянии, но ИТЕРАТОР может выкинуть ошибку но не попртить состояние
    if (m_el->prev->isEmpty) throw std::out_of_range("iterator is out of range");
    m_el = m_el->prev;
    return *this;
}

template <class T>
typename CMyList<T>::CMyListIterator& CMyList<T>::CMyListIterator::operator++()
{
    if (m_el->next->isEmpty) throw std::out_of_range("iterator is out of range");
    m_el = m_el->next;
    return *this;
}

template <class T>
T& CMyList<T>::CMyListIterator::operator*() const
{
    // кейс со стражом (0.5) TODO - пусть будет Done
    if (m_el->isEmpty) throw std::out_of_range("iterator is out of range");
    return *m_el->current.Get();
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
typename CMyList<T>::CMyListIterator CMyList<T>::CMyListIterator::operator--(int) { // разобраться с варнингов TODO (Clang-Tidy) утверждает что постфиксная форма должна возразать константу
    if (this->m_el->prev->isEmpty) throw std::out_of_range("iterator is out of range");
    CMyListIterator retval = *this;
    --(*this);
    return retval;
}

template<class T>
typename CMyList<T>::CMyListIterator CMyList<T>::CMyListIterator::operator++(int) { // разобраться с варнингов TODO (Clang-Tidy) утверждает что постфиксная форма должна возразать константу
    // выход за пределы(кейс) TODO поддержал
    if (this->m_el->next->isEmpty) throw std::out_of_range("iterator is out of range");
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
    return CMyList<T>::CMyListIterator(m_sentinel);
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
void CMyList<T>::AddBegin(T const& current)
{
    auto* newElement = new Element<T>;
    try {
        newElement->current.Construct(current);
    }
    catch (const std::exception& ex) {
        throw ex;
    }
    newElement->isEmpty = false;
    newElement->prev = m_sentinel; // Нужен ли страж в начале добавил страж TODO добавил и надо ПРОВЕРИТЬ
    newElement->next = m_firstElement;

    m_firstElement = newElement;
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
