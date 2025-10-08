
// std 
#include <iostream>
#include <iterator>
#include <algorithm>

// Gtest
#include <gtest/gtest.h>

// local 
#include "array.hpp"


using namespace structures;

template<typename T, typename...Args >
Array<T, sizeof...(Args)> build_array(Args &&... args)
{
    Array<T,sizeof...(Args)> test_array;

    size_t idx = 0; 
    for(auto p : {args...}) {
        test_array[idx] = p;
        idx++;
    }

    return test_array;
} 

template <typename T, size_t N>
void print_array(Array<T,N>& arr)
{   
    for(auto iter = arr.begin(); iter != arr.end(); iter++)
    {
        std::cout<< *iter << std::endl;
    }
}

TEST(TestArrayIteratorMethods, TestIteratorAddDistance) {
    
    int dist = 2;                       // Distance to Move 
    const size_t length = 5;            // Size of Container
    Array<int,length> arr1 = build_array<int>(6,7,8,9, 10);

    // Get Iterator to beginning of Container
    Array<int, length>::iterator it = arr1.begin();

    // Add Distance to Iterator 
    it + dist;

    // Evaluate Validity
    EXPECT_TRUE(*it == 8 );

    // Update Distance & Apply
    dist = 1; 
    it + dist; 

    // Evaluate Validity
    EXPECT_TRUE(*it == 9);
}

TEST(TestArrayIteratorMethods, TestIteratorSubtractDistance) {
    
    int dist = 2;                       // Distance to Move 
    const size_t length = 5;            // Size of Container
    Array<int,length> arr1 = build_array<int>(6,7,8,9, 10);

    // Get Iterator to beginning of Container
    Array<int, length>::iterator it = arr1.end();   // NOTE: End Iter points to the element AFTER the last element of the Container

    // it -6;
    // Add Distance to Iterator 
    it - dist;

    // Evaluate Validity
    EXPECT_TRUE(*it == 9 );

    // Update Distance & Apply
    dist = 3; 
    it - dist; 

    // Evaluate Validity
    EXPECT_TRUE(*it == 6);
}

TEST(TestArrayIteratorMethods, TestIteratorSubtractTwoIterators) {
    const size_t length = 10;                
    int expected_distance = length;
    Array<int, length> arr1 = build_array<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    auto iter_first = arr1.begin(); 
    auto iter_last =  arr1.end(); 

    int ret_distance = iter_last - iter_first;
    EXPECT_TRUE(ret_distance == expected_distance);

    int sub_dist = 5; 
    iter_last - sub_dist; 
    ret_distance = iter_last - iter_first;
    // std::cout << "Returned Distance = " << ret_distance << std::endl;
    EXPECT_TRUE(ret_distance == (expected_distance - sub_dist));
}

TEST(TestArrayIteratorMethods, TestIteratorRangeBaseForLoop) {
    const size_t length = 10;                
    int expected_distance = length;
    Array<int, length> arr1 = build_array<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    // std::cout << "RANGE BASED FOR LOOP" << std::endl;
    int ctr = 0; 
    for(auto p : arr1)
    {
        ctr++;
        // std::cout << p << std::endl;
        EXPECT_EQ(ctr, p);
    }

    EXPECT_EQ(length, ctr);
}

TEST(TestArrayIteratorMethods, TestIteratorBasedForLoop) {
    const size_t length = 10;                
    int expected_distance = length;
    Array<int, length> arr1 = build_array<int>(11, 12, 13, 14, 15, 16, 17, 18, 19, 20);

    // std::cout << "Iter BASED FOR LOOP" << std::endl;
    int ctr = 10; 
    for(Array<int, length>::iterator it = arr1.begin(); it != arr1.end(); ++it)
    {
        ctr++;
        // std::cout << *it << std::endl;
        EXPECT_EQ(ctr, *it);
    }

    // User Lvalue Iterators to test iterator subtraction 
    auto it_b = arr1.begin();
    auto it_e = arr1.end(); 
    EXPECT_EQ(length, ( it_e - it_b));

    EXPECT_EQ(length, (arr1.end() - arr1.begin()));
}

TEST(TestArrayReverseIteratorMethods, TestReverseIteratorBasedForLoop) {
    const size_t length = 10;                
    int expected_distance = length;
    Array<int, length> arr1 = build_array<int>(11, 12, 13, 14, 15, 16, 17, 18, 19, 20);

    int ctr = 20; 
    for(Array<int, length>::reverse_iterator it = arr1.rbegin(); it != arr1.rend(); ++it)
    {
        // std::cout << *it << std::endl;
        EXPECT_EQ(ctr, *it);
        ctr--;
    }

    EXPECT_EQ(length, (arr1.rbegin() - arr1.rend()));
}

TEST(TestArrayPublicMethods, TestArrayInitializerList)
{
    const int first_arr_len = 5; 
    Array<int, 5> my_array {1,2,3,4 ,5};

    const int second_arr_len = 8; 
    Array<int, 8> my_array8 {8, 9, 10, 11, 12, 13, 14, 15};

    EXPECT_TRUE(first_arr_len == my_array.size());
    EXPECT_TRUE(second_arr_len == my_array8.size());

        // std::cout << "MY FUCKING ARRAY" << std::endl;
    int ctr = 0; 
    for(auto p : my_array)
    {   
        EXPECT_EQ(p,++ctr); 
    }

    ctr = 7;
    for(auto p : my_array8)
    {
        EXPECT_EQ(p, ++ctr);
    }
}

TEST(TestArrayPublicMethods, TestArrayDefaultConstructor) {
    Array<int, 5> myArray;

    for(auto p : myArray)
    {
        EXPECT_EQ(p, 0);
    }
}

TEST(TestArrayPublicMethods, TestArraySizeMethod) {
    const size_t expected_len = 10;
    Array<int, expected_len> array {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 

    int length = array.size();
    EXPECT_EQ(length, expected_len);
    EXPECT_NE(length, 11);
    EXPECT_NE(length, 9);
}

TEST(TestArrayPublicMethods, TestArrayAtMethod) {

    const size_t expected_len = 10;
    Array<int, expected_len> array {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    // Test Getting Value from array with "at" method.
    int my_pos = 6; 
    auto value = array.at(my_pos);
    EXPECT_EQ(value, 16);

    // Test Bounds Checking with "at" method.
    my_pos = 11;                    // Position is out of bounds of array
    bool caught_error = false;      // Set default value to false 

    try
    {
        // Accessing out of bounds should throw "ArrayOutOfBounds" exception
        auto bad_value  = array.at(my_pos);
    }
    catch(const ArrayOutOfBoundsException& error) {
        // Catch error and change flag
        caught_error = true;
    }
    EXPECT_TRUE(caught_error);
}

TEST(TestArrayPublicMethods, TestArrayFrontMethod) {
    Array<int, 10> array {2, 4, 6,  8, 10, 12, 14, 16, 18, 20};

    int expected_value = 2; 
    EXPECT_EQ(array.front(), expected_value);

    expected_value = 69;
    array[0] = expected_value;
    EXPECT_EQ(array.front(), expected_value);
}

TEST(TestArrayPublicMethods, TestArrayBackMethod) {
    const int len = 10;
    Array<int, len> array {2, 4, 6,  8, 10, 12, 14, 16, 18, 20};

    int expected_value = 20; 
    EXPECT_EQ(array.back(), expected_value);

    expected_value = 69;
    array.fill(expected_value);
    EXPECT_EQ(array.back(), expected_value);
}

TEST(TestArrayPublicMethods, TestArrayEmptyMethod) {
    const size_t empty_length = 0;
    const size_t length = 10;

    Array<int,empty_length> empty_array;
    Array<int, length> array {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    EXPECT_TRUE(empty_array.empty());
    EXPECT_FALSE(array.empty());
}

TEST(TestArrayPublicMethods, TestArrayDataMethod) {

    const size_t length = 10;
    Array<int, length> array {20, 21, 22, 23, 24, 25, 26, 27, 28, 29};      // Array to Test
    int test_array[length] {20, 21, 22, 23, 24, 25, 26, 27, 28, 29};        // Ground Truth c-array to test against

    // Data returns a pointer to firt element of the private _array inside the Array class
    int* arr_ptr = array.data();    
    EXPECT_NE(arr_ptr, nullptr);        // Pointer Shouldnt not be empty

    // Iterator through every element of the array and test that the ground truth and array values match
    for(int idx =0; idx < length; idx++ )
    {
        int true_val = test_array[idx];
        int test_val = *(arr_ptr + idx);
        EXPECT_EQ(true_val, test_val);
    }
    
}

TEST(TestArrayPublicMethods, TestArrayFillMethod) {

    const size_t length = 10;
    const int test_val = 69;
    Array<int, length> array {2, 4, 6,  8, 10, 12, 14, 16, 18, 20};

    for (int val : array) 
    { 
        EXPECT_NE(val, test_val);
    }

    // Fill the Array
    array.fill(test_val);

    for (int val : array) 
    { 
        EXPECT_EQ(val, test_val);
    }
}

// TEST(TestArrayPublicMethods, TestArraySwapMethod) {

//     const size_t length = 10;
//     Array<int, length> array_1 {1,2,3,4,5,6,7,8,9,10};
//     Array<int, length> array_2 {11,12,13,14,15,16,17,18,19,20};

//     // Test that array values are NOT the same 
//     for (int idx = 0; idx < length; idx++) { EXPECT_NE(array_1[idx], array_2[idx]); }

//     // Swap The contents of Array2 into Array1 
//     array_1.swap(array_2);

//     // Test that array values ARE the same 
//     for (int idx = 0; idx < length; idx++) { EXPECT_EQ(array_1[idx], array_2[idx]); }
// }

// TEST(TestArrayTestUtils, TestArrayBuilder)
// {
//     const size_t my_size = 5;

//     Array<int, my_size> my_arr = build_array<int>(1,2,3,4,5);

//     int idx = 1; 
//     for(auto p : my_arr)
//     {
//         EXPECT_EQ(p, idx);
//         idx++;
//     }
//     print_array<int, my_size>(my_arr); 

// }

// TEST(TestArrayTestUtils, TestArrayPrinter)
// {
//     const size_t my_size = 5;
//     Array<int, my_size> my_arr = build_array<int>(1,2,3,4,5);
//     print_array<int, my_size>(my_arr);
// }

// TEST(TestArrayOperatorComparisons, TestArrayOperatorLT)
// {
//     const size_t my_size = 10;
//     auto arr1 = build_array<int>(1,2,3,4,5,6,7,8,9,10);
//     auto arr2 = build_array<int>(1,2,3,4,5,6,7,8,9,11);
//     EXPECT_LT(arr1, arr2);
// }

// TEST(TestArrayOperatorComparisons, TestArrayOperatorGT)
// {
//     const size_t my_size = 10;
//     auto arr1 = build_array<int>(1,2,3,4,5,6,7,8,9,10);
//     auto arr2 = build_array<int>(1,2,3,4,5,6,7,8,9,11);
//     EXPECT_GT(arr2, arr1);
// }

// TEST(TestArrayOperatorComparisons, TestArrayOperatorLTE)
// {
//     const size_t my_size = 10;
//     auto arr1 = build_array<int>(1,2,3,4,5,6,7,8,9,10);
//     auto arr2 = build_array<int>(1,2,3,4,5,6,7,8,9,11);
//     EXPECT_LE(arr1, arr2);

//     auto arr3 = build_array<int>(1,2,3,4,5);
//     auto arr4 = build_array<int>(1,2,3,4,5);
//     EXPECT_LE(arr3, arr4);
// }

// TEST(TestArrayOperatorComparisons, TestArrayOperatorGTE)
// {
//     const size_t my_size = 10;
//     auto arr1 = build_array<int>(1,2,3,4,5,6,7,8,9,10);
//     auto arr2 = build_array<int>(1,2,3,4,5,6,7,8,9,11);
//     EXPECT_GE(arr2, arr1);

//     auto arr3 = build_array<int>(1,2,3,4,5);
//     auto arr4 = build_array<int>(1,2,3,4,5);
//     EXPECT_LE(arr3, arr4);
// }

// TEST(TestArrayOperatorComparisons, TestArrayOperatorEQ)
// {
//     const size_t my_size = 10;
//     auto arr1 = build_array<int>(1,2,3,4,5);
//     auto arr2 = build_array<int>(1,2,3,4,5);
//     auto arr3 = build_array<int>(1,2,3,4,9);  

//     EXPECT_TRUE(arr1 == arr2);
//     EXPECT_FALSE(arr1 == arr3);
// }

// TEST(TestArrayOperatorComparisons, TestArrayOperatorNEQ)
// {
//     const size_t my_size = 10;
//     auto arr1 = build_array<int>(1,2,3,4,5);
//     auto arr2 = build_array<int>(1,2,3,4,5);
//     auto arr3 = build_array<int>(1,2,3,4,9);

//     EXPECT_TRUE(arr1 != arr3);
//     EXPECT_FALSE(arr1 != arr2);
// }