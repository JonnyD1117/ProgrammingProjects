/**
 * @file array.hpp
 * @brief Implement Array that follow std::array<> API
 * @author Jonathan Dorsey
 * 
 * The goal of this class is to create my own version of an array that complies with C++ std::array 
 * API. Effectively creating a drop in replacement for std::array but using my own logic & underlying
 * structures & design
 */

#pragma once

// std
#include <exception>
#include <initializer_list>
#include <iterator>

// local
#include "vector.hpp"

#include "container_algorithms.hpp"

namespace structures
{

class ArrayOutOfBoundsException : public std::exception
{

} inline ArrayOutOfBounds;

template <typename T, size_t len>
class Array
{

private:
    T _array[len] {};

public:

// Variadic Template allows constructor to accept any number of input args; however, compile time will catch if arguments exceed the fixed length of the array 
template<typename... Args>
Array(Args... args) : _array{args...} {}

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
        using pointer = T*;
        using reference = T&;

        iterator() = default; 

        // Iterator Constructor
        iterator(pointer ptr) : ptr_(ptr) {}

        // Access Operators
        reference operator[](const int pos) { return *(ptr_ + pos); }
        pointer operator->() const { return ptr_; }

        // Read Operators
        reference operator*() const { return *ptr_; }

        // Write/Assignment Operators
        int operator- (iterator& other) { return ptr_ - other.ptr_; }
        int operator- (const iterator& other) { return ptr_ - other.ptr_; }
        iterator& operator- (const int& distance) { ptr_ -= distance; return *this; }
        iterator& operator+ (const int& distance) {  ptr_ += distance; return *this; } 
        iterator& operator- (int& distance) { ptr_ -= distance; return *this; }
        iterator& operator+ (int& distance) {  ptr_ += distance; return *this; } 

        // Iterate Operators
        // ++, --, +=, -==, + -
        iterator& operator++() { ptr_++; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        iterator& operator--() { ptr_--; return *this; }
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
        using const_pointer = const T*;
        using const_reference = const T&;

        // Iterator Constructor
        const_iterator(const_pointer ptr) : ptr_(ptr) {}

        // Access Operators
        // -> , []
        const_reference operator[](const int pos) { return *(ptr_ + pos); }
        const_pointer operator->() const { return ptr_; }

        // Read Operators
        // =*i
        const_reference operator*() const { return *ptr_; }

        // Write/Assignment Operators
        int operator- (const_iterator& other) { return ptr_ - other.ptr_; }
        int operator- (const const_iterator& other) { return ptr_ - other.ptr_; }
        const_iterator& operator- (const int& distance) { ptr_ -= distance; return *this; }
        const_iterator& operator+ (const int& distance) {  ptr_ += distance; return *this; } 
        const_iterator& operator- (int& distance) { ptr_ -= distance; return *this; }
        const_iterator& operator+ (int& distance) {  ptr_ += distance; return *this; } 

        // Iterate Operators
        const_iterator& operator++() { ptr_++; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }

        const_iterator& operator--() { ptr_--; return *this; }
        const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }

        //Comparison Operators
        // ==, !=, <, >, ,+, >=
        bool operator<(const_iterator& other) const { return this->ptr_ < other.ptr_; }
        bool operator== (const_iterator& other) const { return this->ptr_ == other.ptr_; }
        bool operator!= (const_iterator& other) const { return this->ptr_ != other.ptr_; }

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
        using pointer = T*;
        using reference = T&;

        // Iterator Constructor
        reverse_iterator(pointer ptr) : ptr_(ptr) {}

        // Access Operators
        // -> , []
        reference operator[](const int pos) { return *(ptr_ + pos); }
        pointer operator->() const { return ptr_; }

        // Read Operators
        reference operator*() const { return *ptr_; }

        // Write/Assignment Operators
        int operator- (reverse_iterator& other) { return ptr_ - other.ptr_; }
        int operator- (const reverse_iterator& other) { return ptr_ - other.ptr_; }
        reverse_iterator& operator- (int& distance) { ptr_ += distance; return *this; }
        reverse_iterator& operator+ (int distance) {  ptr_ -= distance; return *this; } 
        reverse_iterator& operator- (const int& distance) { ptr_ += distance; return *this; }
        reverse_iterator& operator+ (const int& distance) {  ptr_ -= distance; return *this; } 

        reverse_iterator& operator--() { ptr_++; return *this; }
        reverse_iterator operator--(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }

        // Pre / Post-Increment Operator
        reverse_iterator& operator++() { ptr_ -= 1; return *this; }
        reverse_iterator operator++(int) { reverse_iterator tmp = *this; --(*this); return tmp; }

        //Comparison Operators
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
        using const_pointer = const T*;
        using const_reference = const T&;

        // Iterator Constructor
        const_reverse_iterator(const_pointer ptr) : ptr_(ptr) {}

        // Write/Assignment Operators
        int operator- (const_reverse_iterator& other) { return ptr_ - other.ptr_; }
        int operator- (const const_reverse_iterator& other) { return ptr_ - other.ptr_; }
        const_reverse_iterator& operator- (int& distance) { ptr_ += distance; return *this; }
        const_reverse_iterator& operator+ (int distance) {  ptr_ -= distance; return *this; } 
        const_reverse_iterator& operator- (const int& distance) { ptr_ += distance; return *this; }
        const_reverse_iterator& operator+ (const int& distance) {  ptr_ -= distance; return *this; } 

        const_reverse_iterator& operator--() { ptr_++; return *this; }
        const_reverse_iterator operator--(int) { const_reverse_iterator tmp = *this; ++(*this); return tmp; }

        // Pre / Post-Increment Operator
        const_reverse_iterator& operator++() { ptr_ -= 1; return *this; }
        const_reverse_iterator operator++(int) { const_reverse_iterator tmp = *this; --(*this); return tmp; }



        // Dereference Operator
        const_reference operator*() const { return *ptr_; }
        const_pointer operator->() const { return ptr_; }

        // Pre / Post-Increment Operator
        const_reverse_iterator& operator++() const { ptr_ -= 1; return *this; }
        const_reverse_iterator operator++(int) const { const_iterator tmp = *this; --(*this); return tmp; }

        // Equality / Inequality Operator
        bool operator<(const_reverse_iterator& other) const { return this->ptr_ < other.ptr_; }
        bool operator== (const_reverse_iterator& other) const { return this->ptr_ == other.ptr_; }
        bool operator!= (const_reverse_iterator& other) const { return this->ptr_ != other.ptr_; }

    private:
        const_pointer ptr_;
    };

    // Iterator Methods
    iterator begin() noexcept { return iterator(_array); }
    iterator end() noexcept { return iterator(_array+len); }
    const_iterator cbegin() const noexcept { return const_iterator(_array); }
    const_iterator cend() const noexcept { return const_iterator(_array+len); }
    reverse_iterator rbegin() noexcept { return reverse_iterator(_array + (len-1)); }
    reverse_iterator rend() noexcept { return reverse_iterator(_array-1); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(_array + (len-1)); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(_array-1); }
   
    // Operator Overloading Methods
    T& operator[](size_t pos) {return _array[pos];}

    // Element Access Methods
    T& at(const size_t pos)
    {
        // Check Array Boundary
        if (pos < len)
        {
            return _array[pos];
        }

        throw ArrayOutOfBounds;
    }
    T* data() { return _array; }
    T& front() { return _array[0]; }
    T& back() { return _array[len-1]; }

    // Capacity Methods
    size_t size() { return len; }
    bool empty(){ return (len>0) ? false : true; }

    // Modifier Methods
    void fill(const T& val)
    {
        for(size_t idx =0; idx < len; idx++)
        {
            _array[idx] = val;
        }
    }
    void swap(Array& arr)
    {
        if (this->size() != arr.size())
        {
            throw ArrayOutOfBounds;
        }

        for(size_t idx =0; idx <= len; idx++)
        {
            _array[idx] = arr[idx];
        }
    }
    
    // Operator Comparison Overloads
    bool operator<( Array<T, len>& rhs)
    {
        return algorithms::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end());
    }

    bool operator<( const  Array<T, len>& rhs) const
    {
        return algorithms::lexicographical_compare(this->cbegin(), this->cend(), rhs.cbegin(), rhs.cend());
    }

    bool operator>(const Array<T, len>& rhs) const { return rhs < *this; }

    bool operator>=(const Array<T, len>& rhs) const { return !(*this < rhs); }

    bool operator<=(const Array<T, len>& rhs) const { return !(*this > rhs); }

    bool operator==(const Array<T, len>& rhs) const 
    { 
        return std::equal(this->cbegin(), this->cend(), rhs.cbegin(), rhs.cend()); 
    }

    bool operator==(Array<T, len>& rhs) 
    { 
        return std::equal(this->begin(), this->end(), rhs.begin(), rhs.end()); 
    }

    bool operator!=(const Array<T, len>& rhs) const { return !(*this == rhs); }

};

}