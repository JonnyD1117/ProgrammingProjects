/**
 * @file red_black_tree.hpp
 * @brief Implements a self-balancing Red-Black Tree
 * @author Jonathan Dorsey
 * 
 */

#pragma once

// std 
#include <cstddef>
#include <exception> 
#include <iostream>
#include <iterator>
#include <memory>
#include <string> 
#include <type_traits>
#include <utility>



template<typename Key, typename Value> 
class RedBlackTree
{
    private:

    using kv_t = std::pair<Key,Value>; 

    class enum NodeColor
    {
        RED, 
        BLACK
    };

    struct Node
    {
        Node(Key& key, Value& value): m_key{key}, m_value{value}
        {}

        Node( kv_t& kv_pair) : m_key{kv_pair.first()}, m_value{kv_pair.second()}
        {
        }

        inline Value&     value() const { return m_value; }
        inline Key&       key()   const { return m_key;   }
        inline NodeColor& color() const { return m_color; }

        inline void set_color( const NodeColor color )
        {
            m_color = color;
        }

        Key       m_key   {}; 
        Value     m_value {};
        NodeColor m_color { NodeColor::BLACK };
        std::unique_ptr<Node<Key, Value>> m_left  {nullptr};
        std::unique_ptr<Node<Key, Value>> m_right {nullptr};
    };

    public:

    RedBlackTree(){};

    RedBlackTree( std::initializer_list<kv_t> init_list ) 
    {
        for( auto& kv: init_list )
        {
            this->insert( kv );
        }
    }

    ////////////////////////////////
    //  Public API
    ////////////////////////////////

    Value& at( const Key& key );            // Returns Value (if key exists) ... w/ bounds check

    Value& operator[]( Key&& key );             // Returns value (w/o bounds checking)

    Iterator find( const Key& key );        // Returns iterator given a Key (if key doesn't exists returns "end()" iter)

    bool contains( const Key& key ) const;  // Returns boolean of if key is in container or not. 

    bool empty() const                     // Returns boolean if container is empty or not
    {
        return ( nullptr == m_root );
    }

    size_t size() const;                    //

    void clear();                           // Removes all nodes (clean up memory)

    std::pair<Iterator, bool> insert( const kv_t& kv_pair ) // Inserts a value into tree
    {
        auto& [key, value] = kv_pair;

        if( m_root == nullptr )
        {
            m_root = std::make_unique<Node<Key,Value>( kv_pair );
        }
        else if( value ==  m_root.value() )
        {
            // Value Already Exists (return w/o insertion)
            return std::make_pair<Iterator,bool>( Iterator(), false );
        }
        else
        {
            rb_insert( m_root, kv_pair );

            return;
        }
    }

    template< class... Args >
    std::pair<iterator, bool> emplace( Args&&... args );

    Iterator erase( Iterator pos );

    Iterator begin()
    { 
        return Iterator(&m_data.m_root.get());
    }

    Iterator end()
    {
        return Iterator(&m_data.m_end.get());
    }    

    private:

    std::unique_ptr<Node<Key,Value>> m_root {nullptr};
    std::unique_ptr<Node<Key,Value>> m_end  {nullptr};

    ////////////////////////////////
    //  Private Tree Operations
    ////////////////////////////////

    std::unique_ptr<Node<Key,Value>> rb_insert( std::unique_ptr<Node<Key,Value>> node, kv_t& kv_pair )
    {
        if( kv_pair.second() > node.value())
        {
            //
        }
        else 
        {
            //
        }
    }

    rb_remove();

    rb_clear()
    {
        // Traverse Left 
        // Traverse Right
        // Delete Element
    }


    public:

    struct Iterator 
    { 
    public:
        // Required Aliases
        using iterator_category = std::forward_iterator_tag;
        using value_type        = Value; 
        using difference_type   = std::ptrdiff_t;
        using pointer           = Value*; 
        using reference         = Value&;

        // Constructors
        Iterator(pointer ptr) : m_ptr{ptr} {}
        
        // Core Operators
        reference operator*() const { return *m_ptr; }
        pointer operator->()        { return m_ptr;  }

        // Prefix ++ 
        Iterator& operator++()
        {
            m_ptr++;
            return *this; // In Order Traversal of 
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
};