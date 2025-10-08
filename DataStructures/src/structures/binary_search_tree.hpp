/**
 * @file binary_search_tree.hpp
 * @brief Implements a BST that follow std::map API
 * @author Jonathan Dorsey
 * 
 */

#pragma once

// std 
#include <exception> 
#include <iostream>
#include <memory>
#include <string> 
#include <type_traits>



/*
* Binary Srach Tree
*   1) Dynamically Allocates Nodes (must check with Valgrind)
*   2) 
*/

namespace structures
{

class BstDuplicateValueException : std::exception
{

}inline BstDuplicateValue;

class BstSearchReturnEmptyValueException : std::exception
{

}inline BstSearchReturnEmpty;

template <typename T>
class BinaryNode
{
    public:
    BinaryNode<T>* left, *right = nullptr;

    T data;

    BinaryNode(T val) : data(val) {} 
    BinaryNode(T val, BinaryNode<T>* parent) : data(val) {}
};

template <typename T, typename Node = BinaryNode<T>>
class BinarySearchTree
{
    // Node should be explicitly derived from BinaryNode 
    static_assert(std::is_base_of<BinaryNode<T>, Node>::value, "Node class must be derived from BinaryNode<T>");

    public: 

    BinarySearchTree() = default;

    BinarySearchTree(std::initializer_list<T> il)
    {
        for(auto it=il.begin(); it != il.end(); ++it)
        {
            this->insert_node(*it);
        }
    }

    template <typename InputIterator> 
    BinarySearchTree(InputIterator first, InputIterator last)
    {
        for(auto it=first; it != last; ++it)
        {
            this->insert_node(*it);
        }
    }

    ~BinarySearchTree()
    {
        // Free BST Node memory by recursively walking the tree in order
        free_recursive(this->root);
    }


    /*
    * Bidirectional Iterator & Reverse Iterator
    */
    // class iterator
    // {
    //     // BST Iterator Should traverse "In-Order"
    // public:

    //     // Iterator Type Aliases
    //     using iterator_category = std::bidirectional_iterator_tag;
    //     using value_type = T;
    //     using difference_type = std::ptrdiff_t;
    //     using pointer = Node*;
    //     using reference = Node&;

    //     iterator() = default; 

    //     // Iterator Constructor
    //     iterator(pointer root) : root_(root) 
    //     {
    //         ptr_ = find_minimum(root_);
    //     }

    //     pointer operator->() const { return ptr_; }

    //     // Read Operators
    //     reference operator*() const { return *ptr_; }

    //     // Iterate Operators
    //     // ++, --, +=, -==, + -
    //     iterator& operator++() { ptr_ = ptr_->next; return *this; }
    //     iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

    //     iterator& operator--() { ptr_ = ptr_->previous; return *this; }
    //     iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

    //     //Comparison Operators
    //     bool operator== (const iterator& other) { return this->ptr_ == other.ptr_; }
    //     bool operator!= (const iterator& other) { return this->ptr_ != other.ptr_; }

    // private:

    //     Node* recurse_n_return(Node*& node)
    //     {
    //         if(node == nullptr) return node; 

    //         if (node->left != null) { node->left iterator_recurse_n_return(node->left); }
    //         if (node->right != null) { node->right iterator_recurse_n_return(node->right); }

    //         re

    //     }

    //     pointer ptr_;
    //     pointer root_;
    // };

    // class reverse_iterator
    // {
    // public:

    //     // Iterator Type Aliases
    //     using iterator_category = std::bidirectional_iterator_tag;
    //     using value_type = T;
    //     using difference_type = std::ptrdiff_t;
    //     using pointer = Node<T>*;
    //     using reference = Node<T>&;

    //     reverse_iterator() = default; 

    //     // Iterator Constructor
    //     reverse_iterator(pointer ptr) : ptr_(ptr) {}

    //     pointer operator->() const { return ptr_; }

    //     // Read Operators
    //     reference operator*() const { return *ptr_; }


    //     // Iterate Operators
    //     // ++, --, +=, -==, + -
    //     reverse_iterator& operator++() { ptr_ = ptr_->previous; return *this; }
    //     reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }

    //     reverse_iterator& operator--() { ptr_ = ptr_->next; return *this; }
    //     reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return tmp; }

    //     //Comparison Operators
    //     // ==, !=, <, >, ,+, >=
    //     bool operator== (const reverse_iterator& other) { return this->ptr_ == other.ptr_; }
    //     bool operator!= (const reverse_iterator& other) { return this->ptr_ != other.ptr_; }

    // private:
    //     pointer ptr_;
    // };


    // Public BST Api 
    bool empty() { return is_empty; }                               

    Node* get_root() { return root; }

    Node* search(const T& value) { return search_recursion(root, value); }

    void insert_node(const T& value) 
    {   
        is_empty = false;  
        insert_recursion(this->root, value); 
    }

    void delete_node(const T& value) 
    { 
        delete_recursion(this->root, value); 

        if (this->root == nullptr)
        {
            is_empty = true; 
        }
    }

    void print_tree(int traveral_order=0)
    {
        // NOTE: Print Traversal = {1 : pre-order, 0 : in-order, -1 : post-order }
        print_tree_recursion(this->root, this->root, traveral_order); 
    }

    // rotate_right()
    // rotate_left()
    // rotate_rightleft()
    // rotate_leftright()
    // Traversal (in order, post order, pre-order traversal)
    // Depth/Height
    // Invert

    private:

    void print_tree_recursion(Node*& root, Node*& parent, int print_order)
    {
        if (root == nullptr) { return; }

        else
        {
            // Pre-Order Traversal Printing
            if(print_order == 1) std::cout << "Node::value = " << root->data << "  with Parent = " << parent->data << std::endl;

            // Left Sub-Tree Recursion 
            if(root->left != nullptr) 
            {
                print_tree_recursion(root->left, root, print_order);
            }

            // In-Order Traversal Printing
            if(print_order == 0) std::cout << "Node::value = " << root->data << "  with Parent = " << parent->data << std::endl;

            // Right Sub-Tree Recusion 
            if(root->right != nullptr)
            {
                print_tree_recursion(root->right, root, print_order);
            }

            // Post-Order Traversal Printing
            if(print_order == -1) std::cout << "Node::value = " << root->data << "  with Parent = " << parent->data << std::endl;
        }
    }
    
    // Method Searchs for node with same value -> Return Ptr to Node 
    Node* search_recursion(Node* root, const T& value)
    {
        /*
        * Empty Root Cases
        * 1) BST actual "root" node is empty 
        * 2) BST has recursed through entire tree and failed to find node
        * RESUT: Failed To Find Node
        */
        if(root == nullptr)
        {
            throw BstSearchReturnEmpty;//("BST Search Returned NULL: Node does not exist in BST!");
        } 
        
        else if(root->data == value) { return root; }

        // Left Sub-Tree Recursion 
        else if(value < root->data) 
        {
            return search_recursion(root->left, value);
        }

        // Right Sub-Tree Recusion 
        else
        {
            return search_recursion(root->right, value);
        }
    }

    // Method Searchs for location to insert/delete new node value (checks for duplicates) -> Returns parent node to add/remove child to 
    Node* insert_recursion(Node*& root, const T& value)
    {   
        if(root == nullptr) 
        { 
            root = new Node(value); 
            return root; 
        }

        // Left Sub-Tree Recursion 
        else if(value < root->data)  
        {
            return insert_recursion(root->left,  value);
        }
        // Right Sub-Tree Recusion 
        else
        {
            return insert_recursion(root->right, value);
        }
    }

    Node* delete_recursion(Node*& root, const T& value)
    {   
        // Node is EMPTY return
        if (root == nullptr) { return root; }

        // Value is less than current node value (recurse left subtree)
        else if (value < root->data) { delete_recursion(root->left, value); }

        // Value is greater than curret node value (recurse right subtree)
        else if (value > root->data) { delete_recursion(root->right, value); }

        // Value of Node and Given value MUST be equal (delete the node!)
        else 
        {
            // Delete node with no children 
            if(root->left == nullptr && root->right == nullptr) 
            { 
                delete root; 
                root = nullptr;
                return root; 
            } 
            
            // Delete node with LEFT child   
            else if (root->right == nullptr) 
            { 
                Node* tmp = root; 
                root = root->left; 
                delete tmp;  
                return root; 
            }
            // Delete node with RIGHT child 
            else if (root->left == nullptr) 
            { 
                Node* tmp = root; 
                root = root->right; 
                delete tmp;  
                return root; 
            }
            // Delete node with two children 
            else 
            {
                Node* min_val_node = find_minimum(root->right);             // Find Min Value node in "right" sub-tree
                root->data = min_val_node->data;                            // Overwrite the current root node with the min value node.                            
                root->right = delete_recursion(root->right, root->data);    // Recurse through right subtree and continue deletion 
            }
        }
    }

    Node* free_recursive(Node*& root)
    {
        // Node is EMPTY return
        if (root == nullptr) { return root; }

        if(root->left != nullptr) { root->left = free_recursive(root->left); }

        if (root->right != nullptr) { root->right = free_recursive(root->right); }

        delete root; 
        root = nullptr;
        return root; 
    }

    Node* find_minimum(Node* root)
    {
        if ( root->left == nullptr ) 
        {
            return root; 
        }

        else
        {
            find_minimum(root->left); 
        }
    }

    protected:

    bool is_empty = true;                       // Flag for checking if BST is populated
    Node* root = nullptr;                       // Unique Ptr to root node
};

}    