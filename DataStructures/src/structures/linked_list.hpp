/**
 * @file linked_list.hpp
 * @brief Implements a Doubly-Linked List that follows std::list API
 * @author Jonathan Dorsey
 * 
 */

#pragma once

#include <iostream>
#include <iterator>
#include <exception>
#include <initializer_list>
// #include "vector.hpp"

#include "container_algorithms.hpp"

namespace structures
{

class ListOutOfBoundsException : public std::exception
{

} inline ListOutOfBounds;

template<typename P>
class Node
{
    public: 
    P value;

    Node(P& val) { value = val; }

    void setValue(P val) { value = val; }
    
    Node<P>* previous = nullptr;
    Node<P>* next = nullptr;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Node<U>& node);

    // template<typename I>
    // friend class LinkedList;
};  

template<typename K>
std::ostream& operator<<(std::ostream& os, const Node<K>& node)
{
    if (&node != nullptr)
    {
        os << node.value;
    }
    return os;
}

template <typename T>
class LinkedList
{ 
private:

    Node<T>* root = nullptr;
    Node<T>* tail = root;
    size_t length = 0;

    Node<T>& find(int pos)
    {
        Node<T>* current = nullptr;
        
        if(pos == 0) { current = root; }
        else if(pos > 0) 
        {
            current = root;
            for (int i = 0; i < pos; ++i) 
            { 
                current = current->next;
            }
        } 
        else if(pos < 0) 
        {
            current = tail;
            for (int i = pos; i > 0; --i) 
            { 
                current = current->previous;
            }
        }    
        return *current;  
    }

public:

Node<T>* getRoot() { return root; }
Node<T>* getTail() { return tail; }

LinkedList() = default;

LinkedList(T value)
{
    this->root = new Node<T>(value);
    this->tail = root; 
    ++length;
}

LinkedList(std::initializer_list<T> il)
{
    for(auto it=il.begin(); it != il.end(); ++it)
    {
        this->push_back(*it);
    }
}

template<typename... Args>
LinkedList(Args... args)
{
    for(auto&& i : { args... })
    {
        this->push_back(i);
    }
}

~LinkedList() 
{
    Node<T>* my_node = tail; 
    Node<T>* tmp_node = nullptr;

    while(my_node != nullptr)
    {
        tmp_node = my_node->previous;
        delete my_node;
        my_node = tmp_node; 
    }

    root = nullptr;
    tail = nullptr;
}

    /*
    * Random Access Iterator & Reverse Iterator
    */
    class iterator
    {
    public:

        // Iterator Type Aliases
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = Node<T>*;
        using reference = Node<T>&;

        iterator() = default; 

        // Iterator Constructor
        iterator(pointer ptr) : ptr_(ptr) {}

        // Access Operators
        reference operator[](const int pos) 
        { 
            // Iterate over the List Until reaching index pos
            for(int i=0; i < pos; ++i) { ptr_ = ptr_->next; }
            return *(ptr_); 
        }
        pointer operator->() const { return ptr_; }

        // Read Operators
        reference operator*() const { return *ptr_; }

        // Write/Assignment Operators
        // int operator- (iterator& other) { return ptr_ - other.ptr_; }
        // int operator- (const iterator& other) { return ptr_ - other.ptr_; }
        iterator& operator- (const int& distance) { for(int i =0; i < distance; ++i) {ptr_=ptr_->previous;}  return *this; }
        iterator& operator+ (const int& distance) {  for(int i =0; i < distance; ++i) {ptr_=ptr_->next;} return *this; } 
        iterator& operator- (int& distance) { for(int i =0; i < distance; ++i) {ptr_=ptr_->previous;} return *this; }
        iterator& operator+ (int& distance) {  for(int i =0; i < distance; ++i) {ptr_=ptr_->next;} return *this; } 

        // Iterate Operators
        // ++, --, +=, -==, + -
        iterator& operator++() { ptr_ = ptr_->next; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        iterator& operator--() { ptr_ = ptr_->previous; return *this; }
        iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

        //Comparison Operators
        // ==, !=, <, >, ,+, >=
        bool operator<(const iterator& other) { return this->ptr_ < other.ptr_; }
        bool operator== (const iterator& other) { return this->ptr_ == other.ptr_; }
        bool operator!= (const iterator& other) { return this->ptr_ != other.ptr_; }

    private:
        pointer ptr_;
    };

    class const_iterator
    {
    public:

        // Iterator Type Aliases
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using const_pointer = const Node<T>*;
        using const_reference = const Node<T>&;

        const_iterator() = default; 

        // Iterator Constructor
        const_iterator(const_pointer ptr) : ptr_(ptr) {}

        // Access Operators
        const_reference operator[](const int pos) 
        { 
            // Iterate over the List Until reaching index pos
            for(int i=0; i < pos; ++i) { ptr_ = ptr_->next; }
            return *(ptr_); 
        }
        const_pointer operator->() const { return ptr_; }

        // Read Operators
        const_reference operator*() const { return *ptr_; }

        // Write/Assignment Operators
        // int operator- (iterator& other) { return ptr_ - other.ptr_; }
        // int operator- (const iterator& other) { return ptr_ - other.ptr_; }
        const_iterator& operator- (const int& distance) const { for(int i =0; i < distance; ++i) {ptr_=ptr_->previous;}  return *this; }
        const_iterator& operator+ (const int& distance) const {  for(int i =0; i < distance; ++i) {ptr_=ptr_->next;} return *this; } 
        const_iterator& operator- (int& distance) const { for(int i =0; i < distance; ++i) {ptr_=ptr_->previous;} return *this; }
        const_iterator& operator+ (int& distance) const {  for(int i =0; i < distance; ++i) {ptr_=ptr_->next;} return *this; } 

        // Iterate Operators
        // ++, --, +=, -==, + -
        const_iterator& operator++() { ptr_ = ptr_->next; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }

        const_iterator& operator--() { ptr_ = ptr_->previous; return *this; }
        const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }

        //Comparison Operators
        // ==, !=, <, >, ,+, >=
        bool operator<(const const_iterator& other) const { return this->ptr_ < other.ptr_; }
        bool operator== (const const_iterator& other) const { return this->ptr_ == other.ptr_; }
        bool operator!= (const const_iterator& other) const { return this->ptr_ != other.ptr_; }

    private:
        const_pointer ptr_;
    };

    class reverse_iterator
    {
    public:

        // Iterator Type Aliases
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = Node<T>*;
        using reference = Node<T>&;

        reverse_iterator() = default; 

        // Iterator Constructor
        reverse_iterator(pointer ptr) : ptr_(ptr) {}

        // Access Operators
        reference operator[](const int pos) 
        { 
            // Iterate over the List Until reaching index pos
            for(int i=0; i < pos; ++i) { ptr_ = ptr_->previous; }
            return *(ptr_); 
        }
        pointer operator->() const { return ptr_; }

        // Read Operators
        reference operator*() const { return *ptr_; }

        // Write/Assignment Operators
        // int operator- (iterator& other) { return ptr_ - other.ptr_; }
        // int operator- (const iterator& other) { return ptr_ - other.ptr_; }
        reverse_iterator& operator- (const int& distance) { for(int i =0; i < distance; ++i) {ptr_=ptr_->next;}  return *this; }
        reverse_iterator& operator+ (const int& distance) {  for(int i =0; i < distance; ++i) {ptr_=ptr_->previous;} return *this; } 
        reverse_iterator& operator- (int& distance) { for(int i =0; i < distance; ++i) {ptr_=ptr_->next;} return *this; }
        reverse_iterator& operator+ (int& distance) {  for(int i =0; i < distance; ++i) {ptr_=ptr_->previous;} return *this; } 

        // Iterate Operators
        // ++, --, +=, -==, + -
        reverse_iterator& operator++() { ptr_ = ptr_->previous; return *this; }
        reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }

        reverse_iterator& operator--() { ptr_ = ptr_->next; return *this; }
        reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return tmp; }

        //Comparison Operators
        // ==, !=, <, >, ,+, >=
        bool operator<(const reverse_iterator& other) { return this->ptr_ < other.ptr_; }
        bool operator== (const reverse_iterator& other) { return this->ptr_ == other.ptr_; }
        bool operator!= (const reverse_iterator& other) { return this->ptr_ != other.ptr_; }

    private:
        pointer ptr_;
    };

    class const_reverse_iterator
    {
    public:

        // Iterator Type Aliases
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using const_pointer = const Node<T>*;
        using const_reference = const Node<T>&;

        const_reverse_iterator() = default; 

        // Iterator Constructor
        const_reverse_iterator(const_pointer ptr) : ptr_(ptr) {}

        // Access Operators
        const_reference operator[](const int pos) 
        { 
            // Iterate over the List Until reaching index pos
            for(int i=0; i < pos; ++i) { ptr_ = ptr_->previous; }
            return *(ptr_); 
        }
        const_pointer operator->() const { return ptr_; }

        // Read Operators
        const_reference operator*() const { return *ptr_; }

        // Write/Assignment Operators
        // int operator- (iterator& other) { return ptr_ - other.ptr_; }
        // int operator- (const iterator& other) { return ptr_ - other.ptr_; }
        const_reverse_iterator& operator- (const int& distance) const { for(int i =0; i < distance; ++i) {ptr_=ptr_->next;}  return *this; }
        const_reverse_iterator& operator+ (const int& distance) const {  for(int i =0; i < distance; ++i) {ptr_=ptr_->previous;} return *this; } 
        const_reverse_iterator& operator- (int& distance) const { for(int i =0; i < distance; ++i) {ptr_=ptr_->next;} return *this; }
        const_reverse_iterator& operator+ (int& distance) const {  for(int i =0; i < distance; ++i) {ptr_=ptr_->previous;} return *this; } 

        // Iterate Operators
        // ++, --, +=, -==, + -
        const_reverse_iterator& operator++() { ptr_ = ptr_->previous; return *this; }
        const_reverse_iterator operator++(int) { const_reverse_iterator tmp = *this; ++(*this); return tmp; }

        const_reverse_iterator& operator--() { ptr_ = ptr_->next; return *this; }
        const_reverse_iterator operator--(int) { const_reverse_iterator tmp = *this; --(*this); return tmp; }

        //Comparison Operators
        // ==, !=, <, >, ,+, >=
        bool operator<(const const_reverse_iterator& other) const { return this->ptr_ < other.ptr_; }
        bool operator== (const const_reverse_iterator& other) const { return this->ptr_ == other.ptr_; }
        bool operator!= (const const_reverse_iterator& other) const { return this->ptr_ != other.ptr_; }

    private:
        const_pointer ptr_;
    };

    // Iterator Methods
    iterator begin() noexcept { return iterator(root); }
    iterator end() noexcept { return iterator(tail->next); }
    const_iterator cbegin() const noexcept { return const_iterator(root); }
    const_iterator cend() const noexcept { return const_iterator(tail->next); }
    reverse_iterator rbegin() noexcept { return reverse_iterator(tail); }
    reverse_iterator rend() noexcept { return reverse_iterator(root->previous); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(tail); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(root->previous); }
   
    // Operator Overloading Methods
    T& operator[](int pos) { return find(pos).value; }
    T& front() { return root->value; }
    T& back() { return tail->value; }
    T& at(int pos)
    {
        if(pos > length) { throw ListOutOfBounds; } 
        return find(pos).value;
    }

    // Capacity Methods
    size_t size() { return length; }
    bool empty(){ return (length>0) ? false : true; }

    // Modifier Methods
    // void assign()
    // emplace_back()
    // emplace_front()

    void pop_front()
    {
        Node<T>* cur_root = root; 
        root = cur_root->next;
        root->previous = nullptr;

        delete cur_root;
        --length;
    }

    void pop_back()
    {
        Node<T>* cur_tail = tail; 

        tail = cur_tail->previous;
        tail->next = nullptr;
        delete cur_tail;
        --length;
    }

    void push_front(T value)
    {       
        Node<T>* new_node = new Node<T>(value);             // Heap Allocated and Init new Node of Type T 

        if (tail == nullptr && root == nullptr)
        {
            root = new_node;
            tail = root;
            root->next = nullptr;
            root->previous = nullptr;
        }
        else 
        {
            Node<T>* cur_root = root;
            cur_root->previous = new_node ; 
            cur_root->previous->next = cur_root; 
            root = cur_root->previous; 
            root->previous = nullptr;
            // ASSERT_NE(cur_root, root);
        }

        ++length;      
    }

    void push_back(T value)
    {       
        Node<T>* new_node = new Node<T>(value);             // Heap Allocated and Init new Node of Type T 

        if (tail == nullptr && root == nullptr)
        {
            root = new_node;
            tail = root;
            root->next = nullptr;
            root->previous = nullptr;
        }
        else 
        {
            Node<T>* cur_tail = tail;
            cur_tail->next = new_node ; 
            cur_tail->next->previous = cur_tail; 
            tail = cur_tail->next; 
            tail->next = nullptr;
            // ASSERT_NE(cur_tail, tail);
        }

        ++length;      
    }

    void clear()
    {
        Node<T>* my_node = tail; 
        Node<T>* tmp_node = nullptr;

        while(my_node != nullptr)
        {
            tmp_node = my_node->previous;
            delete my_node;
            my_node = tmp_node; 
        }

        root = nullptr;
        tail = nullptr;
        length = 0; 
    }

    // emplace()
    // insert
    // erase

    // void resize(size_t n, T&& value)
    // {
    //     if (n == length) { return; }

    //     else if (n < length) 
    //     {
    //         Node<T>* my_node = root; 
    //         Node<T>* tmp_node = nullptr;

    //         for(int ctr = 0; ctr < n; ++ctr)
    //         {
    //             tmp_node = my_node->previous;
    //             my_node = tmp_node; 
    //         }

    //         for(int ctr = n; ctr < length; ++ctr)
    //         {
    //             tmp_node = my_node->next;
    //             delete my_node;
    //             my_node = tmp_node; 
    //             --length;
    //         }
    //     } 

    //     else if (n > length)
    //     {

    //     }
    // }



    // void swap(Array& arr)
    // {
    //     if (this->size() != arr.size())
    //     {
    //         throw ArrayOutOfBounds;
    //     }

    //     for(size_t idx =0; idx <= len; idx++)
    //     {
    //         _array[idx] = arr[idx];
    //     }
    // }
    
    // Operator Comparison Overloads
    // bool operator<( Array<T, len>& rhs)
    // {
    //     return algorithms::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end());
    // }

    // bool operator<( const  Array<T, len>& rhs) const
    // {
    //     return algorithms::lexicographical_compare(this->cbegin(), this->cend(), rhs.cbegin(), rhs.cend());
    // }

    // bool operator>(const Array<T, len>& rhs) const { return rhs < *this; }

    // bool operator>=(const Array<T, len>& rhs) const { return !(*this < rhs); }

    // bool operator<=(const Array<T, len>& rhs) const { return !(*this > rhs); }

    // bool operator==(const Array<T, len>& rhs) const 
    // { 
    //     return std::equal(this->cbegin(), this->cend(), rhs.cbegin(), rhs.cend()); 
    // }

    // bool operator==(Array<T, len>& rhs) 
    // { 
    //     return std::equal(this->begin(), this->end(), rhs.begin(), rhs.end()); 
    // }

    // bool operator!=(const Array<T, len>& rhs) const { return !(*this == rhs); }

    // Operation Methods

    // splice
    // remove
    // remove_if
    // unique
    // merge
    // sort
    // reverse
};

}