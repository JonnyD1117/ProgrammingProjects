// std
#include <algorithm>
#include <array>
#include <iostream>
#include <initializer_list>
#include <vector>

#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t


template<typename T, size_t Size=100>
class b_plus_tree
{
    T[Size] m_data {};

    b_plus_tree(std::initializer_list<T> list)
    {
        std::copy(list.begin(), list.end(), m_data);
    }

    struct Node
    {
        std::array<Node*> 
    };

public: 

    struct Iterator 
    { 
    public:
        // Required Aliases
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T; 
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*; 
        using reference         = T&;

        // Constructors
        Iterator(pointer ptr) : m_ptr{ptr} {}
        
        // Core Operators
        reference operator*() const { return *m_ptr; }
        pointer operator->()        { return m_ptr;  }

        // Prefix ++ 
        Iterator& operator++()
        {
            m_ptr++;
            return *this;
        }

        // Postfix ++ 
        Iterator operator++(int)
        {
            Iterator tmp = *this; ++(*this); return tmp;
        }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }


    private:
        pointer m_ptr;


    };

public:
    Iterator begin()
    { 
        return Iterator(&m_data[0]);
    }

    Iterator end()
    {
        return Iterator(&m_data[100]);
    }    

};