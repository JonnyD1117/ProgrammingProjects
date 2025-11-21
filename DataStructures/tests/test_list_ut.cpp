// std

// GTest
#include <gtest/gtest.h>

// Local
#include "linked_list.hpp"


using namespace structures;


TEST(TestLinkedListBasic, ListMethodPushback)
{
    LinkedList<int> list; 
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    int ctr = 1; 
    Node<int>* myNode = list.getRoot();

    while(true)
    {
        EXPECT_EQ(myNode->value, ctr);
        myNode = myNode->next;

        if(myNode == nullptr) { break; }
        ++ctr;
    }
}

TEST(TestLinkedListBasic, ListMethodPushfront)
{
    LinkedList<int> list; 
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    list.push_front(5);

    int ctr = 5; 
    Node<int>* myNode = list.getRoot();

    while(true)
    {
        EXPECT_EQ(myNode->value, ctr);
        myNode = myNode->next;

        if(myNode == nullptr) { break; }
        --ctr;
    }
}

TEST(TestLinkedListIterator, TestForwardListIterator)
{
    LinkedList<int> list; 
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    int ctr = 1; 

    for(auto it = list.begin(); it != list.end(); ++it)
    {
        EXPECT_EQ(it->value, ctr );
        ++ctr;
    }
}

TEST(TestLinkedListIterator, TestReverseListIterator)
{
    LinkedList<int> list; 
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    int ctr = 5; 

    for(auto rev_it = list.rbegin(); rev_it != list.rend(); ++rev_it)
    {
        EXPECT_EQ(rev_it->value, ctr);
        --ctr;
    }
}

TEST(TestLinkedListBasic, ListDefaultConstructor) {
    LinkedList<int> List;
    Node<int>* myNode = List.getRoot();
    EXPECT_EQ(myNode, nullptr);
}

TEST(TestLinkedListBasic, ListSingleValueOverloadConstructor) {
    LinkedList<int> List(5);

    Node<int>* myNode = List.getRoot();
    EXPECT_NE(myNode, nullptr);
    EXPECT_EQ(myNode->value, 5);
}

TEST(TestLinkedListBasic, ListInitializerListOverloadConstructor) {
    LinkedList<int> List {1,2,3,4,5,6,7,8,9,10};

    Node<int>* myNode = List.getRoot();
    EXPECT_NE(myNode, nullptr);
    int ctr = 1; 
    for(auto it = List.begin() ; it != List.end(); ++it)
    {
        EXPECT_EQ(myNode->value, ctr);
        myNode = myNode->next; 
        ++ctr;
    }
}

TEST(TestLinkedListBasic, ListVariadicParamPackOverloadConstructor) {
    
    LinkedList<int> myList(69, 12, 34,56,78,9);
    EXPECT_EQ(myList.size(), 6);
}


TEST(TestLinkedListBasic, ListDestructor) {
    
    LinkedList<int>* myHeapList = new LinkedList<int>();

    myHeapList->push_back(1); 
    myHeapList->push_back(2); 
    myHeapList->push_back(3); 
    myHeapList->push_back(4); 
    myHeapList->push_back(5); 

    Node<int>* list_root = myHeapList->getRoot();
    Node<int>* list_tail = myHeapList->getTail();

    EXPECT_NE(list_root, nullptr); 
    EXPECT_NE(list_tail, nullptr);

    Node<int>* tmp_node = list_root;  

    for(int i = 1; i < 6; ++i)
    {   
        EXPECT_EQ(tmp_node->value, i); 
        tmp_node = tmp_node->next;
    }

    delete myHeapList; 
}

TEST(TestLinkedListBasic, ListMethodFront) {
    
    LinkedList<int> myList1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    LinkedList<int> myList2 {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    EXPECT_EQ(myList1.front(), 0);
    EXPECT_EQ(myList2.front(), 9);
}

TEST(TestLinkedListBasic, ListMethodBack) {
    
    LinkedList<int> myList1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    LinkedList<int> myList2 {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    EXPECT_EQ(myList1.back(), 9);
    EXPECT_EQ(myList2.back(), 0);
}

TEST(TestLinkedListBasic, ListMethodSize) {
    
    LinkedList<int> myList1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    LinkedList<int> myList2;
    LinkedList<int> myList3(69);
    LinkedList<int> myList4(69, 12, 34,56,78,9);

    EXPECT_EQ(myList1.size(), 10);
    EXPECT_EQ(myList2.size(), 0 );
    EXPECT_EQ(myList3.size(), 1);
    EXPECT_EQ(myList4.size(), 6);
}

TEST(TestLinkedListBasic, ListMethodEmpty) {
    
    LinkedList<int> myList1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    LinkedList<int> myList2;

    EXPECT_FALSE(myList1.empty());
    EXPECT_TRUE(myList2.empty());
}

TEST(TestLinkedListBasic, ListSubscriptOperator) {
    
    LinkedList<int> myList1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for(int i = 0 ; i < 10; ++i)
    {
        EXPECT_EQ(myList1[i], i);
    }
}

TEST(TestLinkedListBasic, ListAtMethod) {
    
    LinkedList<int> myList1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // Test Bounds Checking with "at" method.
    int my_pos = 11;                    // Position is out of bounds of vector
    bool caught_error = false;      // Set default value to false 

    try
    {
        // Accessing out of bounds should throw "ArrayOutOfBounds" exception
        auto bad_value  = myList1.at(my_pos);
    }
    catch(const ListOutOfBoundsException& error) {
        // Catch error and change flag
        caught_error = true;
    }
    EXPECT_TRUE(caught_error);
}

TEST(TestLinkedListBasic, ListPopFrontMethod) {
    
    LinkedList<int> myList1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    myList1.pop_front();
    EXPECT_EQ(myList1.size(), 9);
    myList1.pop_front();
    EXPECT_EQ(myList1.size(), 8);
    myList1.pop_front();
    EXPECT_EQ(myList1.size(), 7);

    // Test Random Access Value
    EXPECT_EQ(myList1[0], 3);
    EXPECT_EQ(myList1[3], 6);
    EXPECT_EQ(myList1[6], 9);
}

TEST(TestLinkedListBasic, ListPopBackMethod) {
    
    LinkedList<int> myList1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    myList1.pop_back();
    EXPECT_EQ(myList1.size(), 9);
    myList1.pop_back();
    EXPECT_EQ(myList1.size(), 8);
    myList1.pop_back();
    EXPECT_EQ(myList1.size(), 7);

    // Test Random Access Value
    EXPECT_EQ(myList1[0], 0);
    EXPECT_EQ(myList1[3], 3);
    EXPECT_EQ(myList1[6], 6);
}

TEST(TestLinkedListBasic, ListClearMethod) {
    
    LinkedList<int> myList1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(myList1.size(), 10);
    myList1.clear();
    EXPECT_EQ(myList1.size(), 0);
}