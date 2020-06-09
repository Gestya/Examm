#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H

#include <cstdlib>
#include <list>
#include <stdexcept>

template<class T>
struct Node
{
    Node<T>* next = { nullptr };
    T data;
};

// -----------------------------------------------------

template<class T>
class SingleLinkedList
{
public:
    SingleLinkedList()
        : begin{nullptr}
        , count{0}
    {

    }
    ~SingleLinkedList();

    void add(const T& data);
    const T& get(size_t index) const;
    T& get(size_t index);
    bool erase(size_t index);

    size_t size() const;

private:
    Node<T>* find_node(size_t index);

    Node<T>* begin = { nullptr };
    size_t count = { 0 };
};

// -----------------------------------------------------

template<class T>
SingleLinkedList<T>::~SingleLinkedList()
{
    Node<T>* node = begin;
    while (node)
    {
        Node<T>* next = node->next;
        delete node;
        node = next;
    }
}

template<class T>
void SingleLinkedList<T>::add(const T& data)
{
    Node<T>* new_node = new Node<T>();
    new_node->data = data;

    if (!begin)
    {
        begin = new_node;
    }
    else
    {
        Node<T>* last_node = begin;
        while (last_node->next)
            last_node = last_node->next;
        last_node->next = new_node;
    }

    count++;
}

template<class T>
Node<T>* SingleLinkedList<T>::find_node(size_t index)
{
    if (index < count)
    {
        Node<T>* node = begin;
        while (index)
        {
            node = node->next;
            index--;
        }

        return node;
    }

    return nullptr;
}

template<class T>
const T& SingleLinkedList<T>::get(size_t index) const
{
    Node<T>* node = find_node(index);
    if (node)
        return node->data;

    throw std::out_of_range("Node with specified index does not exist");
}

template<class T>
T& SingleLinkedList<T>::get(size_t index)
{
    Node<T>* node = find_node(index);
    if (node)
        return node->data;

    throw std::out_of_range("Node with specified index does not exist");
}

template<class T>
bool SingleLinkedList<T>::erase(size_t index)
{
    if (index >= count)
        return false;

    Node<T>* removed_node = {nullptr};
    if (index)
    {
        Node<T>* prev_node = find_node(index - 1);
        removed_node = prev_node->next;
        prev_node->next = removed_node->next;
    }
    else
    {
        removed_node = begin;
        begin = begin->next;
    }
    delete removed_node;

    count--;

    return true;
}

template<class T>
size_t SingleLinkedList<T>::size() const
{
    return count;
}

#endif // SINGLELINKEDLIST_H
