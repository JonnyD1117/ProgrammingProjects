/**
 * @file map.hpp
 * @brief Implements a Red-Black BST that follow std::map API
 * @author Jonathan Dorsey
 * 
 */

#pragma once

#include <iostream>
#include <exception>
#include <iterator>
#include <initializer_list>

namespace structures
{

class MapOutOfBoundsException : std::exception
{

}inline MapOutOfBounds;


// template < class Key, map::key_type           class T,  map::mapped_type   class Compare = less<Key>,                     // map::key_compare           class Alloc = allocator<pair<const Key,T> >    // map::allocator_type           > class ma
template<typename Key_t, typename Value_t>
class Map
{

    private:

    

    public: 

    // Constructor & Destructors
    Map() = default;
    ~Map(); 

    // PUBLIC ITERATORS 

    // iterator begin() noexcept;
    // iterator end() noexcept;

    // reverse_iterator rbegin() noexcept;
    // reverse_iterator rend() noexcept;

    // const_iterator cbegin() const noexcept;
    // const_iterator cend() const noexcept;

    // const_reverse_iterator crbegin() const noexcept;
    // const_reverse_iterator crend() const noexcept;



    // PUBLIC METHODS
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    Value_t& operator[] (const Key_t& k);
    Value_t& operator[] (Key_t&& k);

    mapped_type& at (const key_type& k);const mapped_type& at (const key_type& k) const;

    single element (1)	

pair<iterator,bool> insert (const value_type& val);template <class P> pair<iterator,bool> insert (P&& val);

with hint (2)	

iterator insert (const_iterator position, const value_type& val);template <class P> iterator insert (const_iterator position, P&& val);

range (3)	

template <class InputIterator>  void insert (InputIterator first, InputIterator last);

initializer list (4)	

void insert (initializer_list<value_type> il);

(1)	

iterator  erase (const_iterator position);

(2)	

size_type erase (const key_type& k);

(3)	

iterator  erase (const_iterator first, const_iterator last);

void swap (map& x);

void clear() noexcept;

template <class... Args>  pair<iterator,bool> emplace (Args&&... args);

template <class... Args>  iterator emplace_hint (const_iterator position, Args&&... args);

key_compare key_comp() const;

value_compare value_comp() const;

iterator find (const key_type& k);const_iterator find (const key_type& k) const;

size_type count (const key_type& k) const;

iterator lower_bound (const key_type& k);const_iterator lower_bound (const key_type& k) const;

iterator upper_bound (const key_type& k);const_iterator upper_bound (const key_type& k) const;

pair<const_iterator,const_iterator> equal_range (const key_type& k) const;pair<iterator,iterator>             equal_range (const key_type& k);





};

}