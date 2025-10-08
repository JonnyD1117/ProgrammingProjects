/**
 * @file vector.hpp
 * @brief Implements a vector that follows std::vector API
 * @author Jonathan Dorsey
 * 
 */


#pragma once

#include <iostream>
#include <exception>
#include <iterator>
#include <utility>
#include <initializer_list>

namespace structures
{

class VectorOutOfBoundsException : std::exception
{

}inline VectorOutOfBounds;

template<typename T>
class Vector
{
private:
    size_t cur_size = 0;            // The current "used" size of the container
    size_t cur_capacity = 0;        // The current "capacity" of the container
    T* current = nullptr;           // Pointer to the last populated element of container
    T* array = nullptr;             // The raw data array that vector is wrapping

public:

    /*
    * Iterator Definitions
    */
    class iterator {
    public:

        // Iterator Type Aliases
        using iterator_category = std::random_access_iterator_tag;
        using value_type = Vector<T>;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T &;

        // Iterator Constructor
        iterator(pointer ptr) : ptr_(ptr) {}

        // Dereference Operator
        reference operator[](const int pos) { return *(ptr_ + pos); }
        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }

        // Write/Assignment Operators
        int operator- (iterator& other) { return ptr_ - other.ptr_; }
        int operator- (const iterator& other) { return ptr_ - other.ptr_; }
        iterator& operator- (const int& distance) { ptr_ -= distance; return *this; }
        iterator& operator+ (const int& distance) {  ptr_ += distance; return *this; } 
        iterator& operator- (int& distance) { ptr_ -= distance; return *this; }
        iterator& operator+ (int& distance) {  ptr_ += distance; return *this; } 

        // Pre / Post-Increment Operator
        iterator& operator++() { ptr_ += 1; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        iterator& operator--() { ptr_--; return *this; }
        iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

        // Equality / Inequality Operator
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
    iterator begin() noexcept { return iterator(array); }
    iterator end() noexcept { return iterator(array+cur_size); }
    const_iterator cbegin() const noexcept { return const_iterator(array); }
    const_iterator cend() const noexcept { return const_iterator(array+cur_size); }
    reverse_iterator rbegin() noexcept { return reverse_iterator(array + (cur_size-1)); }
    reverse_iterator rend() noexcept { return reverse_iterator(array-1); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(array + (cur_size-1)); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(array-1); }
   
   /*
    * Constructors & Destructors
    */

    Vector() = default;                                             // Default Constructor  
    
    Vector(size_t n) 
    { 
        array = new T[n]; 
        cur_capacity = n; 
        cur_size = n; 
        current = array;
    }
    
    Vector(size_t n, const T& val)
    {   
        // Create raw array
        array = new T[n];
        current = array + (n - 1);                  // Update `current` ptr to last pos of raw array
        // Popular Raw array with values
        for(size_t idx = 0; idx < n; idx++) { array[idx] = val; }
        cur_capacity = n; 
        cur_size = n; 
    }

    template<typename InputIterator>
    Vector(InputIterator first, InputIterator last)
    {
        for(InputIterator it=first; it != last; it++)
        {
            this->push_back(*it);
        }
    }

    Vector(std::initializer_list<T> il)
    {
        array = new T[il.size()];
        for(auto it=il.begin(); it != il.end(); ++it)
        {
            this->push_back(*it);
        }
    }

    ~Vector() { delete[] array; }

    
    /*
     * Capacity Methods
     */
    size_t size() { return cur_size; }
    void resize(size_t count, T value=0)
    {
        if(cur_size > count)
        {
            T* tmp_array = new T[count];
            for(int i=0; i< count; i++) { tmp_array[i] = array[i]; }
            delete[] array;
            array = tmp_array;
        }
        else
        {
            // Extend to count and default values to given value parameter
            T* tmp_array = new T[count];
            for(int i=0; i < count; i++)
            {
                if(i < cur_size)
                {
                    tmp_array[i] = array[i];
                }
                else
                {
                    tmp_array[i] = value;
                }

            }
            delete[] array;
            array = tmp_array;
        }

        cur_size = count;
        cur_capacity = count;
        current = &array[count];
    };
    size_t capacity() { return cur_capacity; }
    bool empty() { return (cur_size == 0) ? true : false; }
    void reserve(size_t n)
    {
        if(n < cur_capacity) { return; }
        else if (n > cur_capacity)
        {
            T* tmp_array = new T[n];
            for(int i=0; i< n; i++) { tmp_array[i] = array[i]; }
            delete[] array;
            array = tmp_array;
            cur_capacity = n;
        }
    }
    void shrink_to_fit()
    {
        T* tmp_arr  = new T[cur_size];

        for(int i=0; i<cur_size; i++) { tmp_arr[i] = array[i]; }

        delete[] array;
        array = tmp_arr;

        // Capacity needs to reflect resizing
        cur_capacity = cur_size;
    };

    /* 
     * Element Access Methods
     */
    T& operator[](size_t index) { return array[index]; }
    T& at(size_t idx)
    {
        if( idx > cur_capacity) { throw VectorOutOfBounds;  }
        return array[idx];
    }
    T& front() {  return array[0]; }
    T& back() {  return *current; }
    T* data(){ return array; }

    /*
     * Modifier Methods
     */

    // void assign(std::initializer_list<T> il) {}

    void assign(size_t n, const T& val) 
    {
        this->resize(n, val);
        // // No Forced Re-Allocation ()
        // if (this->size() < n)
        // {

        //     this->resize(n, val);
        // //    int ctr = 0; 
        // //    for(auto it = this->begin(); it != this->end(); ++it)
        // //    {
        // //         if (ctr < n)
        // //         {
        // //             array[ctr] = val;
        // //         }
        // //         else
        // //         {
        // //             array[ctr] = 0;
        // //         }

        // //         ++ctr;
        // //    }

        // //    cur_size = n;
        // //    current = array + n ;
        // }
        // else if (n > this->capacity())
        // {
        //     array = new T[n];
        //     for(int i = 0; i< n; ++i)
        //     {
        //         array[i] = val;
        //     }
        //     cur_size = n;
        //     cur_capacity = n;
        //     current = array + n ;
        // }
    }
    
    // template<typname InputIterator>
    // void assign(InputIterator first, InputIterator last) {}

    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        if(cur_size == 0)
        {
            cur_capacity++;
            array = new T[cur_capacity];
        }

        else if(cur_size == cur_capacity)
        {
            T* tmp_arr = new T[2 * cur_capacity];

            // Move All Data from previous array to tmp array
            for(int i=0; i<=cur_capacity; i++) { tmp_arr[i] = array[i]; }

            // Update Capacity, Free prev array, & Assign tmp ptr to array
            cur_capacity *= 2;
            delete[] array;
            array = tmp_arr;
        }

        // Complete Emplace Back by forwarding variadic args to type constructor

        new (&array[cur_size]) T(std::forward<Args>(args)...);
        // array[cur_size] = data;
        current = &array[cur_size];
        cur_size++;
    };
    

    void push_back(const T& data)
    {
        if(cur_size == 0)
        {
            cur_capacity++;
            array = new T[cur_capacity];

            array[cur_size] = data;
            current = &array[cur_size];
            cur_size++;
            return;
        }

        if(cur_size == cur_capacity)
        {
            T* tmp_arr = new T[2 * cur_capacity];

            // Move All Data from previous array to tmp array
            for(int i=0; i<=cur_capacity; i++) { tmp_arr[i] = array[i]; }

            // Update Capacity, Free prev array, & Assign tmp ptr to array
            cur_capacity *= 2;
            delete[] array;
            array = tmp_arr;
        }

        // Complete PushBack, Get current element, Incr size.
        array[cur_size] = data;
        current = &array[cur_size];
        cur_size++;
    };
    
    void pop_back()
    {
        array[cur_size] = 0;
        cur_size--;
        current = &array[cur_size];
    };
    // insert
    // erase
    void swap(Vector& vector)
    {   
        Vector::iterator it  = this->begin();

        for(auto element : vector)
        {   
            *it = element; 
            ++it; 
        }
    }
    void clear()
    {
        for(int i=0; i<=cur_capacity; i++) { array[i] = 0; }
        cur_size = 0;
        current = nullptr;
    };
    // emplace
    // emplace_back    

    
    /*
    * Operator Overloads
    */
   bool operator== (Vector<T>& rhs)
   {

    size_t vect1_size = this->size();

    if(vect1_size != rhs.size()) { return false; }

    else
    {
        for(int i =0; i < vect1_size; i++)
        {
            if((*this)[i] != rhs[i])
            {
                return false;
            }
        }
        return true;
    }

   }
};

}