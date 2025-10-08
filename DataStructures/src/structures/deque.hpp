/**
 * @file deque.hpp
 * @brief Implements a Deque that follow std::deque API
 * @author Jonathan Dorsey
 * 
 */

#pragma once

#include <iostream>
#include <exception>
#include <iterator>
#include <initializer_list>
#include <utility> 
#include "vector.hpp"

/* 
* INSERATION RULES
* 1) If push_front and cur_array_ptr != cur_blk_head_ptr then...
*       1.1) Increment cur_array_ptr + 1 
        1.2) At the address of cur_array_ptr insert pushed value
* 2) if push_front and cur_ptr == block_head_ptr 
*      2.1) Allocate new Block
*      2.2) Update maps "head_block_ptr" to new block
*      2.3) Set cur_array_ptr equal to block_tail_ptr
*      2.4) Add pushed value to location of the cur_array_ptr 
* 
* 3) if push_back and cur_array_ptr != tail_blk_ptr then 
        3.1) decrement cur_array_ptr -1 
        3.2) Insert new vlaue into cur_array_ptr
* 4) if push_back and cur_ptr == tail_blk_ptr then ... 
*      4.1) Allocate new block 
*      4.2) Update maps "tail_block_ptr" to new block
*      4.3) Set current curr_array_ptr equal to block's head_ptr
*      4.4) Insert Value into address of curr_array_ptr 
* 
* DELETION RULES
* 1) If pop_front and cur_block_ptr != tail_block_ptr 
*      1.1) copy  value from cur_array_ptr
*      1.2) Null value in cur_array_ptr  
*      1.3) Decrement cur_block_ptr -1
*      1.4) Return value popped off array
* 2) If pop_front and cur_array_Ptr == tail_block_ptr
*      2.1) Copy value at cur_array_ptr 
       2.2) Dellocate head_block
       2.3) decrement head_block_ptr
       2.4) set cur_element_ptr == block_head_ptr
* 
* 
* MAP ALLOCATION RULES
* Init) Allocate Default Map

// GROW MAP
if (head_block_it == head_it || tail_block_it == tail_it )               // Head OR Tail of map is FULL expand map

    // Resize the vector for 2*map.capacity()
    // Shift elements to middle of Vector using clever std::rotate (or should I implement std::rotate)
    // 

else()                                                                  //  Map is Not full at either Head or tail

// SHRINK MAP

if ( map.capacity()  > 4*std::distance(head_block_it, tail_block_it) )  // Map is HUGE reduce the size

    // Create a New vector using the previous maps iterators
    // Once new map is populate shift elements to the right appriopriate offset
    // set new map equal to old map 

map


* 
* 
* FORWARD ITERATION RULES

1) start at head_block_it 
2) get the block at that iterator 
3) Iterate over block array from block_head_element_it to block_tail_element_it 
4) while (iterator != tail_block_it)


* 
* 
* REVERSE ITERATION RULES
* 
* 
*/




namespace structures
{

    enum class BlockReference
    {
        HEAD, 
        TAIL,
        MIDDLE
    };

    class BlockArrayOutOfBoundsException : std::exception
    {

    }inline BlockArrayOutOfBounds;

    // Block Structure 
    template<typename T, size_t block_size=1024>
    class Block
    {
        private:

        using blockArray_ptr_t = T*;
    
        blockArray_ptr_t p_arr_head = nullptr;                            // Ptr to Array head e.g. array[0]
        blockArray_ptr_t p_arr_tail = nullptr;                            // Ptr to Array tail e.g. array[-1]
        blockArray_ptr_t p_element_head = nullptr;                        // Ptr to Blocks current head element
        blockArray_ptr_t p_element_tail = nullptr;                        // Ptr to Blocks current tail element

        BlockReference ref_type = BlockReference::MIDDLE;

        public:

        Block()
        {
            p_arr_head = new T[block_size];                                // Dynamically allocate the block array
            p_arr_tail =  p_arr_head + ( block_size -1 );                 // Ptr arithmetic to define ptr to arrays tail element   

            ref_type = BlockReference::MIDDLE;

            // Set the Element Pointers to the middle of the Array
            p_element_head = p_arr_head + ( block_size / 2 );             // By Default construct the block using Middle Referencing
            p_element_tail = p_arr_head + ( block_size / 2 );             // Tail block is the same as the head block when empty    
        }

        Block(BlockReference type)
        {
            p_arr_head = new T[block_size];                                // Dynamically allocate the block array
            p_arr_tail =  p_arr_head + ( block_size -1 );                 // Ptr arithmetic to define ptr to arrays tail element  

            if (type == BlockReference::HEAD)
            {
                // Set the Element Pointers to the 0th element of the Array
                p_element_head = p_arr_head;
                p_element_tail = p_arr_head;
            }   
            else if (type == BlockReference::TAIL)
            {
                // Set the Element Pointers to the final element of the Array
                p_element_head = p_arr_tail;
                p_element_tail = p_arr_tail;
            }  

            else 
            {
                // Set the Element Pointers to the middle of the Array
                p_element_head = p_arr_head + ( block_size / 2 );
                p_element_tail = p_arr_head + ( block_size / 2 );   
            }

        }

        ~Block() { delete[] p_arr_head; }                 // De-Allocate array on object destruction

        void push_back( T&& value) 
        {   
            // if incrementing the pointer will NOT overflow array
            if (p_element_tail < p_arr_tail)
            {
                ++p_element_tail;
                *p_element_tail = value;
            } 

            else
            {
                // throw BlockArrayOutOfBounds("Attempted Block::push_back() has overflowed the block array bounds!");
            }
            
            
        }

        void push_front( T&& value ) 
        {
            // if incrementing the pointer will NOT overflow array
            if (p_element_head > p_arr_head)
            {
                --p_element_head;
                *p_element_head = value;
            } 

            else
            {
                // throw BlockArrayOutOfBounds("Attempted Block::push_front() has overflowed the block array bounds!");
            }
        } 

        T pop_back() 
        {
            T& array_element = *p_element_tail;

            *p_element_tail = 0;

            ++p_element_tail; 

            return array_element;
        }
        T pop_front()
        {
            T& array_element = *p_element_head;

            *p_element_head = 0;

            --p_element_head; 

            return array_element;
        }

    };

}

// class DequeOutOfBoundsException : std::exception
// {

// }inline DequeOutOfBounds;


// template<typename T>
// class Deque
// {
//     private:

//     enum class BlockReference
//     {
//         HEAD, 
//         TAIL,
//         MIDDLE
//     };

//     class BlockArrayOutOfBoundsException : std::exception
//     {

//     }inline BlockArrayOutOfBounds;

//     // Block Structure 
//     template<size_t block_size=1024>
//     class Block
//     {
//         private:

//         using blockArray_ptr_t = T*;
    
//         blockArray_ptr_t p_arr_head = nullptr;                            // Ptr to Array head e.g. array[0]
//         blockArray_ptr_t p_arr_tail = nullptr;                            // Ptr to Array tail e.g. array[-1]
//         blockArray_ptr_t p_element_head = nullptr;                        // Ptr to Blocks current head element
//         blockArray_ptr_t p_element_tail = nullptr;                        // Ptr to Blocks current tail element

//         BlockReference ref_type = NULL;

//         public:

//         Block()
//         {
//             p_arr_head = new [block_size];                                // Dynamically allocate the block array
//             p_arr_tail =  p_arr_head + ( block_size -1 );                 // Ptr arithmetic to define ptr to arrays tail element   

//             ref_type = BlockReference::MIDDLE;

//             // Set the Element Pointers to the middle of the Array
//             p_element_head = p_arr_head + ( block_size / 2 );             // By Default construct the block using Middle Referencing
//             p_element_tail = p_arr_head + ( block_size / 2 );             // Tail block is the same as the head block when empty    
//         }

//         Block(BlockReference type)
//         {
//             p_arr_head = new [block_size];                                // Dynamically allocate the block array
//             p_arr_tail =  p_arr_head + ( block_size -1 );                 // Ptr arithmetic to define ptr to arrays tail element  

//             if (type == BlockReference::HEAD)
//             {
//                 // Set the Element Pointers to the 0th element of the Array
//                 p_element_head = p_arr_head;
//                 p_element_tail = p_arr_head;
//             }   
//             else if (type == BlockReference::TAIL)
//             {
//                 // Set the Element Pointers to the final element of the Array
//                 p_element_head = p_arr_tail;
//                 p_element_tail = p_arr_tail;
//             }  

//             else 
//             {
//                 // Set the Element Pointers to the middle of the Array
//                 p_element_head = p_arr_head + ( block_size / 2 );
//                 p_element_tail = p_arr_head + ( block_size / 2 );   
//             }

//         }

//         ~Block() { delete[] p_arr_head; }                 // De-Allocate array on object destruction

//         void push_back( T& value) 
//         {   
//             // if incrementing the pointer will NOT overflow array
//             if (p_element_tail < p_arr_tail)
//             {
//                 ++p_element_tail;
//                 *p_element_tail = value;
//             } 

//             else
//             {
//                 throw BlockArrayOutOfBounds("Attempted Block::push_back() has overflowed the block array bounds!");
//             }
            
            
//         }

//         void push_front( T& value ) 
//         {
//             // if incrementing the pointer will NOT overflow array
//             if (p_element_head > p_arr_head)
//             {
//                 --p_element_head;
//                 *p_element_head = value;
//             } 

//             else
//             {
//                 throw BlockArrayOutOfBounds("Attempted Block::push_front() has overflowed the block array bounds!");
//             }
//         } 

//         T pop_back() 
//         {
//             T& array_element = *p_element_tail;

//             *p_element_tail = 0;

//             ++p_element_tail; 

//             return array_element;
//         }
//         T pop_front()
//         {
//             T& array_element = *p_element_head;

//             *p_element_head = 0;

//             --p_element_head; 

//             return array_element;
//         }

//     };


//     // Deque Member Initialization
//     static const size_t array_size = 1024;
//     size_t map_size = 8;

//     // Define pointer to block of Type T and Size block_size
//     using block_ptr_t = Block<array_size>*;
//     using VectorIterator = Vector<block_ptr_t>::iterator;

//     // Array of Pointers to "Blocks" (e.g. map)
//     Vector<block_ptr_t> block_map;

//     // Deque Book Keeping Pointers
//     VectorIterator map_head_it;
//     VectorIterator map_tail_it; 
//     VectorIterator deque_head_it;
//     VectorIterator deque_tail_it;  

//     public: 

//     Deque()
//     {
//         // Create Initial Map & Book keeping iterators
//         block_map = create_init_map();
//     }

//     ~Deque(); 

//     // PUBLIC ITERATORS 

//     // iterator begin() noexcept;
//     // iterator end() noexcept;

//     // reverse_iterator rbegin() noexcept;
//     // reverse_iterator rend() noexcept;

//     // const_iterator cbegin() const noexcept;
//     // const_iterator cend() const noexcept;

//     // const_reverse_iterator crbegin() const noexcept;
//     // const_reverse_iterator crend() const noexcept;





//     // // PUBLIC METHODS
//     // size_t size();
//     // size_t max_size();
//     // void resize(size_t n);
//     // void resize(size_tn, const T& val);
//     // void shrink_to_fit();

//     // T& at(size_t n);
//     // const T& at(size_t n) const; 
//     // T& front(); 
//     // const T& front() const; 
//     // T& back(); 
//     // const T& back() const; 

//     // template<typname InputIterator>
//     // void assign(InputIterator first, InputIterator last); 
//     // void assign(size_t n, const T& val);
//     // void assign(std::initializer_list<T> il);

//     // void push_back(const T& val)
//     // {

//     //     // 


//     //     /*
//     //     * BACK END INSERATION RULES
//     //     * 3) if push_back and cur_array_ptr != tail_blk_ptr then 
//     //             3.1) decrement cur_array_ptr -1 
//     //             3.2) Insert new vlaue into cur_array_ptr
//     //     * 4) if push_back and cur_ptr == tail_blk_ptr then ... 
//     //     *      4.1) Allocate new block 
//     //     *      4.2) Update maps "tail_block_ptr" to new block
//     //     *      4.3) Set current curr_array_ptr equal to block's head_ptr
//     //     *      4.4) Insert Value into address of curr_array_ptr 
//     //     */



//     // }
//     // void push_back(T&& val);


//     // /*
//     // * INSERATION RULES
//     // * 1) If push_front and cur_array_ptr != cur_blk_head_ptr then...
//     // *       1.1) Increment cur_array_ptr + 1 
//     //         1.2) At the address of cur_array_ptr insert pushed value
//     // * 2) if push_front and cur_ptr == block_head_ptr 
//     // *      2.1) Allocate new Block
//     // *      2.2) Update maps "head_block_ptr" to new block
//     // *      2.3) Set cur_array_ptr equal to block_tail_ptr
//     // *      2.4) Add pushed value to location of the cur_array_ptr 
//     // */

//     // void push_front(const T& val) { };
//     // void push_front(T&& val);


//     // void pop_back();
//     // void pop_front();

//     // void swap(Deque& x);

//     // void clear() noexcept; 

//     // T& operator[](size_t pos) 
//     // // const T& operator[](size_t pos) const; 

//     // //template <typename... Args> 
//     // // iterator emplace(const_iterator positio, Args&&... args);

//     // template <class... Args>  
//     // void emplace_front (Args&&... args);

//     // template <class... Args>  
//     // void emplace_back (Args&&... args);




//     // // iterator erase (const_iterator position );
//     // // iterator erase (const_iterator first, const_iterator last );

//     // // single element (1)	
//     // // iterator insert (const_iterator position, const value_type& val);

//     // // fill (2)	
//     // // iterator insert (const_iterator position, size_type n, const value_type& val);

//     // // range (3)	
//     // // template <class InputIterator>iterator insert (const_iterator position, InputIterator first, InputIterator last);

//     // // move (4)	
//     // // iterator insert (const_iterator position, value_type&& val);

//     // // initializer list (5)	
//     // // iterator insert (const_iterator position, initializer_list<value_type> il);




//     // // PUBLIC DEQUE RELATIONAL OPERATORS

//     // // (1)	
//     // // template <class T, class Alloc>  bool operator== (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);

//     // // (2)	
//     // // template <class T, class Alloc>  bool operator!= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);

//     // // (3)	
//     // // template <class T, class Alloc>  bool operator<  (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);

//     // // (4)	
//     // // template <class T, class Alloc>  bool operator<= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);

//     // // (5)	
//     // // template <class T, class Alloc>  bool operator>  (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);

//     // // (6)	
//     // // template <class T, class Alloc>  bool operator>= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);

//     // private:

//     // block_ptr_t get_deque_head() { return *deque_head_it }
//     // block_ptr_t get_deque_tail() { return *deque_tail_it; }

//     // void append_head_block()
//     // {
//     //     // Create a new head Block
//     //     block_ptr_t new_block = new Block<T, block_size>();
        
//     //     deque_head_it--; 

//     //     if((deque_head_it - 1) == map_head_it)
//     //     {
//     //         // Deque Head == Map Head (out of growing space in front)
//     //         // Reallocate map, move data, & shift map to middle of new vector
//     //         block_map = reallocate_map(block_map);
//     //     }

//     //     // Add Block to Map
//     //     *deque_head_it = new_block; 
//     // }

//     // VectorIterator append_tail_block()
//     // {
//     //     // Create a new tail Block
//     //     block_ptr_t new_block = new Block<T, block_size>();
        
//     //     deque_tail_it++; 

//     //     if((deque_tail_it + 1) == map_tail_it)
//     //     {
//     //         // Deque Tail == Map Tail (out of growing space in back)
//     //         // Re-allocate map, move data, & shift map to middle of new vector
//     //         block_map = reallocate_map(block_map);
//     //     }

//     //     // Add Block to Map
//     //     *deque_tail_it = new_block; 
//     // }

//     void create_init_map(size_t size)
//     {
//         /*
//         Creates the map with an initial block using Middle 
//         */
//         size_t offset = (size / 2 - 1); 

//         // Resize the Map vector
//         block_map.resize(size, nullptr);

//         // Define Maps Iterators 
//         map_head_it = block_map.begin(); 
//         map_tail_it = block_map.end() - 1; 
        
//         // Define Initial Deque Iterators at Middel of Map 
//         deque_head_it = block.begin() + offset;
//         deque_tail_it = block.begin() + offset;

//         // Allocate Maps first Block
//         block_map[offset] = ( new Block<block_size>());

//         // Invoke Helper function to setup blocks internal pointers
//         // set_block_to_mid_idx(block_map[offset]);
//     }


//     // Vector<block_ptr_t> extend_map(Vector<block_ptr_t>& map)
//     // {
//     //     // Re-allocate Map (vector::resize())

//     //     // Shift Element to middle of Map via offset (std::rotate...etc)

//     //     // Book Keep Iterators & such
//     // }

//     // Vector<block_ptr_t> shrink_map(Vector<block_ptr_t>& map)
//     // {
//     //     // void shift_vector(Vector<block_ptr_t>& map, size_t offset);

//     //     // Re-allocate Map

//     //     // Shift Element to middle of Map via offset (std::rotate...etc)

//     //     // 
//     // }

// };
// }


// //     /*
// //     * Iterator Definitions
// //     */
// //     class iterator {
// //     public:

// //         // Iterator Type Aliases
// //         using iterator_category = std::random_access_iterator_tag;
// //         using value_type = Vector<T>;
// //         using difference_type = std::ptrdiff_t;
// //         using pointer = T*;
// //         using reference = T &;

// //         // Iterator Constructor
// //         iterator(pointer ptr) : ptr_(ptr) {}

// //         // Dereference Operator
// //         reference operator[](const int pos) { return *(ptr_ + pos); }
// //         reference operator*() const { return *ptr_; }
// //         pointer operator->() const { return ptr_; }

// //         // Write/Assignment Operators
// //         int operator- (iterator& other) { return ptr_ - other.ptr_; }
// //         int operator- (const iterator& other) { return ptr_ - other.ptr_; }
// //         iterator& operator- (const int& distance) { ptr_ -= distance; return *this; }
// //         iterator& operator+ (const int& distance) {  ptr_ += distance; return *this; } 
// //         iterator& operator- (int& distance) { ptr_ -= distance; return *this; }
// //         iterator& operator+ (int& distance) {  ptr_ += distance; return *this; } 

// //         // Pre / Post-Increment Operator
// //         iterator& operator++() { ptr_ += 1; return *this; }
// //         iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

// //         iterator& operator--() { ptr_--; return *this; }
// //         iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

// //         // Equality / Inequality Operator
// //         bool operator<(const iterator& other) { return this->ptr_ < other.ptr_; }
// //         bool operator== (const iterator& other) { return this->ptr_ == other.ptr_; }
// //         bool operator!= (const iterator& other) { return this->ptr_ != other.ptr_; }

// //     private:
// //         pointer ptr_;
// //     };

// //     class const_iterator
// //     {
// //     public:

// //         // Iterator Type Aliases
// //         using iterator_category = std::random_access_iterator_tag;
// //         using value_type = T;
// //         using difference_type = std::ptrdiff_t;
// //         using const_pointer = const T*;
// //         using const_reference = const T&;

// //         // Iterator Constructor
// //         const_iterator(const_pointer ptr) : ptr_(ptr) {}

// //         // Access Operators
// //         // -> , []
// //         const_reference operator[](const int pos) { return *(ptr_ + pos); }
// //         const_pointer operator->() const { return ptr_; }

// //         // Read Operators
// //         // =*i
// //         const_reference operator*() const { return *ptr_; }

// //         // Write/Assignment Operators
// //         int operator- (const_iterator& other) { return ptr_ - other.ptr_; }
// //         int operator- (const const_iterator& other) { return ptr_ - other.ptr_; }
// //         const_iterator& operator- (const int& distance) { ptr_ -= distance; return *this; }
// //         const_iterator& operator+ (const int& distance) {  ptr_ += distance; return *this; } 
// //         const_iterator& operator- (int& distance) { ptr_ -= distance; return *this; }
// //         const_iterator& operator+ (int& distance) {  ptr_ += distance; return *this; } 

// //         // Iterate Operators
// //         const_iterator& operator++() { ptr_++; return *this; }
// //         const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }

// //         const_iterator& operator--() { ptr_--; return *this; }
// //         const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }

// //         //Comparison Operators
// //         // ==, !=, <, >, ,+, >=
// //         bool operator<(const_iterator& other) const { return this->ptr_ < other.ptr_; }
// //         bool operator== (const_iterator& other) const { return this->ptr_ == other.ptr_; }
// //         bool operator!= (const_iterator& other) const { return this->ptr_ != other.ptr_; }

// //     private:
// //         const_pointer ptr_;
// //     };

// //     class reverse_iterator
// //     {
// //     public:

// //         // Iterator Type Aliases
// //         using iterator_category = std::random_access_iterator_tag;
// //         using value_type = T;
// //         using difference_type = std::ptrdiff_t;
// //         using pointer = T*;
// //         using reference = T&;

// //         // Iterator Constructor
// //         reverse_iterator(pointer ptr) : ptr_(ptr) {}

// //         // Access Operators
// //         // -> , []
// //         reference operator[](const int pos) { return *(ptr_ + pos); }
// //         pointer operator->() const { return ptr_; }

// //         // Read Operators
// //         reference operator*() const { return *ptr_; }

// //         // Write/Assignment Operators
// //         int operator- (reverse_iterator& other) { return ptr_ - other.ptr_; }
// //         int operator- (const reverse_iterator& other) { return ptr_ - other.ptr_; }
// //         reverse_iterator& operator- (int& distance) { ptr_ += distance; return *this; }
// //         reverse_iterator& operator+ (int distance) {  ptr_ -= distance; return *this; } 
// //         reverse_iterator& operator- (const int& distance) { ptr_ += distance; return *this; }
// //         reverse_iterator& operator+ (const int& distance) {  ptr_ -= distance; return *this; } 

// //         reverse_iterator& operator--() { ptr_++; return *this; }
// //         reverse_iterator operator--(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }

// //         // Pre / Post-Increment Operator
// //         reverse_iterator& operator++() { ptr_ -= 1; return *this; }
// //         reverse_iterator operator++(int) { reverse_iterator tmp = *this; --(*this); return tmp; }

// //         //Comparison Operators
// //         bool operator<(const reverse_iterator& other) { return this->ptr_ < other.ptr_; }
// //         bool operator== (const reverse_iterator& other) { return this->ptr_ == other.ptr_; }
// //         bool operator!= (const reverse_iterator& other) { return this->ptr_ != other.ptr_; }

// //     private:
// //         pointer ptr_;
// //     };

// //     class const_reverse_iterator
// //     {
// //     public:

// //         // Iterator Type Aliases
// //         using iterator_category = std::random_access_iterator_tag;
// //         using value_type = T;
// //         using difference_type = std::ptrdiff_t;
// //         using const_pointer = const T*;
// //         using const_reference = const T&;

// //         // Iterator Constructor
// //         const_reverse_iterator(const_pointer ptr) : ptr_(ptr) {}

// //         // Write/Assignment Operators
// //         int operator- (const_reverse_iterator& other) { return ptr_ - other.ptr_; }
// //         int operator- (const const_reverse_iterator& other) { return ptr_ - other.ptr_; }
// //         const_reverse_iterator& operator- (int& distance) { ptr_ += distance; return *this; }
// //         const_reverse_iterator& operator+ (int distance) {  ptr_ -= distance; return *this; } 
// //         const_reverse_iterator& operator- (const int& distance) { ptr_ += distance; return *this; }
// //         const_reverse_iterator& operator+ (const int& distance) {  ptr_ -= distance; return *this; } 

// //         const_reverse_iterator& operator--() { ptr_++; return *this; }
// //         const_reverse_iterator operator--(int) { const_reverse_iterator tmp = *this; ++(*this); return tmp; }

// //         // Pre / Post-Increment Operator
// //         const_reverse_iterator& operator++() { ptr_ -= 1; return *this; }
// //         const_reverse_iterator operator++(int) { const_reverse_iterator tmp = *this; --(*this); return tmp; }



// //         // Dereference Operator
// //         const_reference operator*() const { return *ptr_; }
// //         const_pointer operator->() const { return ptr_; }

// //         // Pre / Post-Increment Operator
// //         const_reverse_iterator& operator++() const { ptr_ -= 1; return *this; }
// //         const_reverse_iterator operator++(int) const { const_iterator tmp = *this; --(*this); return tmp; }

// //         // Equality / Inequality Operator
// //         bool operator<(const_reverse_iterator& other) const { return this->ptr_ < other.ptr_; }
// //         bool operator== (const_reverse_iterator& other) const { return this->ptr_ == other.ptr_; }
// //         bool operator!= (const_reverse_iterator& other) const { return this->ptr_ != other.ptr_; }

// //     private:
// //         const_pointer ptr_;
// //     };