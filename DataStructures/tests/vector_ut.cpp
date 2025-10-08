#include <gtest/gtest.h>
#include "vector.hpp"

using namespace structures;

template<typename T, typename... Args>
Vector<T> build_vector(Args &&... args)
{
    Vector<T> test_vector {args...};

    return test_vector;
} 

template <typename T>
void print_vector(Vector<T>& vector)
{   
    for(auto iter = vector.begin(); iter != vector.end(); iter++)
    {
        std::cout<< *iter << std::endl;
    }
}

TEST(TestVectorBuild, BuildVector)
{
    Vector<int> vec = build_vector<int>(0, 1,2,3,4,5,6,7,8,9);

    for(int idx =0 ; idx < 10; idx++)
    {
        EXPECT_EQ(vec[idx], idx);
    }
}

TEST(TestVectorIteratorMethods, TestIteratorAddDistance) {
    
    int dist = 2;                       // Distance to Move 
    Vector<int> vec1 = build_vector<int>(6,7,8,9, 10);

    // Get Iterator to beginning of Container
    Vector<int>::iterator it = vec1.begin();

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

TEST(TestVectorIteratorMethods, TestIteratorSubtractDistance) {
    
    int dist = 2;                       // Distance to Move 
    Vector<int> vec1 = build_vector<int>(6,7,8,9, 10);

    // Get Iterator to beginning of Container
    Vector<int>::iterator it = vec1.end();   // NOTE: End Iter points to the element AFTER the last element of the Container

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

TEST(TestVectorIteratorMethods, TestIteratorSubtractTwoIterators) {
    int expected_distance = 10;
    Vector<int> vec1 = build_vector<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    auto iter_first = vec1.begin(); 
    auto iter_last =  vec1.end(); 

    int ret_distance = iter_last - iter_first;
    EXPECT_TRUE(ret_distance == expected_distance);

    int sub_dist = 5; 
    iter_last - sub_dist; 
    ret_distance = iter_last - iter_first;
    // std::cout << "Returned Distance = " << ret_distance << std::endl;
    EXPECT_TRUE(ret_distance == (expected_distance - sub_dist));
}

TEST(TestVectorIteratorMethods, TestIteratorRangeBaseForLoop) {
    int expected_distance = 10;
    Vector<int> vec1 = build_vector<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    // std::cout << "RANGE BASED FOR LOOP" << std::endl;
    int ctr = 0; 
    for(auto p : vec1)
    {
        ctr++;
        // std::cout << p << std::endl;
        EXPECT_EQ(ctr, p);
    }

    EXPECT_EQ(10, ctr);
}

TEST(TestVectorIteratorMethods, TestIteratorBasedForLoop) {
    const size_t length = 10;                
    int expected_distance = length;
    Vector<int> vec1 = build_vector<int>(11, 12, 13, 14, 15, 16, 17, 18, 19, 20);

    // std::cout << "Iter BASED FOR LOOP" << std::endl;
    int ctr = 10; 
    for(Vector<int>::iterator it = vec1.begin(); it != vec1.end(); ++it)
    {
        ctr++;
        // std::cout << *it << std::endl;
        EXPECT_EQ(ctr, *it);
    }

    // User Lvalue Iterators to test iterator subtraction 
    auto it_b = vec1.begin();
    auto it_e = vec1.end(); 
    EXPECT_EQ(length, ( it_e - it_b));

    EXPECT_EQ(length, (vec1.end() - vec1.begin()));
}

TEST(TestVectorReverseIteratorMethods, TestReverseIteratorBasedForLoop) {
    const size_t length = 10;                
    int expected_distance = length;
    Vector<int> vec1 = build_vector<int>(11, 12, 13, 14, 15, 16, 17, 18, 19, 20);

    int ctr = 20; 
    for(Vector<int>::reverse_iterator it = vec1.rbegin(); it != vec1.rend(); ++it)
    {
        // std::cout << *it << std::endl;
        EXPECT_EQ(ctr, *it);
        ctr--;
    }

    EXPECT_EQ(length, (vec1.rbegin() - vec1.rend()));
}

TEST(TestVectorPublicMethods, TestVectorInitializerList)
{
    const int first_vec_len = 5; 
    Vector<int> my_vector {1,2,3,4 ,5};

    const int second_vec_len = 8; 
    Vector<int> my_vector8 {8, 9, 10, 11, 12, 13, 14, 15};

    EXPECT_TRUE(first_vec_len == my_vector.size());
    EXPECT_TRUE(second_vec_len == my_vector8.size());

        // std::cout << "MY FUCKING ARRAY" << std::endl;
    int ctr = 0; 
    for(auto p : my_vector)
    {   
        EXPECT_EQ(p,++ctr); 
    }

    ctr = 7;
    for(auto p : my_vector8)
    {
        std::cout << "My Vector" << p << std::endl;
        EXPECT_EQ(p, ++ctr);
    }
}

TEST(TestVectorPublicMethods, TestVectorDefaultConstructor) {
    Vector<int> myVector;

    for(auto p : myVector)
    {
        std::cout << p << std::endl;
        EXPECT_EQ(p, 0);
    }
}

TEST(TestVectorPublicMethods, TestVectorAtMethod) {

    const size_t expected_len = 10;
    Vector<int> vec {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    // Note.... vector capacity can be larger than number of elements put into vector resize the vector for a better test
    vec.shrink_to_fit();

    // Test Getting Value from vector with "at" method.
    int my_pos = 6; 
    auto value = vec.at(my_pos);
    EXPECT_EQ(value, 16);

    // Test Bounds Checking with "at" method.
    my_pos = 11;                    // Position is out of bounds of vector
    bool caught_error = false;      // Set default value to false 

    try
    {
        // Accessing out of bounds should throw "ArrayOutOfBounds" exception
        auto bad_value  = vec.at(my_pos);
    }
    catch(const VectorOutOfBoundsException& error) {
        // Catch error and change flag
        caught_error = true;
    }
    EXPECT_TRUE(caught_error);
}

TEST(TestVectorPublicMethods, TestVectorFrontMethod) {
    Vector<int> vec {2, 4, 6,  8, 10, 12, 14, 16, 18, 20};

    int expected_value = 2; 
    EXPECT_EQ(vec.front(), expected_value);

    expected_value = 69;
    vec[0] = expected_value;
    EXPECT_EQ(vec.front(), expected_value);
}

TEST(TestVectorPublicMethods, TestVectorBackMethod) {
    const int len = 10;
    Vector<int> vec {2, 4, 6,  8, 10, 12, 14, 16, 18, 20};
    Vector<int> vec_swap {69, 69, 69, 69, 69, 69, 69, 69, 69, 69};

    int expected_value = 20; 
    EXPECT_EQ(vec.back(), expected_value);

    expected_value = 69;
    vec.swap(vec_swap);
    EXPECT_EQ(vec.back(), expected_value);
}

TEST(TestVectorPublicMethods, TestVectorEmptyMethod) {
    const size_t empty_length = 0;
    const size_t length = 10;

    Vector<int> empty_vec;
    Vector<int> vec {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    EXPECT_TRUE(empty_vec.empty());
    EXPECT_FALSE(vec.empty());
}

TEST(TestVectorPublicMethods, TestVectorCapacityMethod) {
    const size_t length = 10;
    Vector<int> vec {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    EXPECT_GE(vec.capacity(),length);

    vec.reserve(length*length);

    EXPECT_EQ(vec.capacity(), length*length);
}

TEST(TestVectorPublicMethods, TestVectorSizeMethod) {
    const size_t length = 10;
    Vector<int> vec {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    EXPECT_EQ(vec.size(),length);

    vec.push_back(10);
    vec.push_back(11);
    vec.push_back(12); 

    int expected_len = length + 3; 

    EXPECT_EQ(vec.size(), expected_len);

    int ctr = 0; 
    for(auto p : vec) { ctr++; }
    EXPECT_EQ(ctr, expected_len);
}

TEST(TestVectorPublicMethods, TestVectorResizeMethod) {
    size_t length = 11;
    Vector<int> vec {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    EXPECT_EQ(vec.size(),length);

    size_t new_len = 100; 
    vec.resize(new_len);

    EXPECT_EQ(vec.size(), new_len);
    EXPECT_EQ(vec[2],2);
    EXPECT_EQ(vec.back(), 0);

    vec.resize(length);
    EXPECT_EQ(vec.size(),length);

}

TEST(TestVectorPublicMethods, TestVectorShrinkToFitMethod) {
    size_t length = 11;
    Vector<int> vec {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    EXPECT_EQ(vec.size(),length);

    vec.reserve(length*length);
    EXPECT_EQ(vec.capacity(), length*length);

    vec.shrink_to_fit();

    EXPECT_EQ(vec.size(), vec.capacity());
    EXPECT_EQ(vec.size(), length);
}

TEST(TestVectorPublicMethods, TestVectorReserveMethod) {
    size_t length = 100;
    size_t reserve_len = 256; 
    Vector<int> vec(length);

    EXPECT_EQ(vec.size(), length);
    EXPECT_EQ(vec.size(), vec.capacity());

    vec.reserve(reserve_len);
    EXPECT_EQ(vec.capacity(), reserve_len);
    EXPECT_NE(vec.size(), vec.capacity());
}

TEST(TestVectorPublicMethods, TestVectorDataMethod) {

    const size_t length = 10;
    Vector<int> vec {20, 21, 22, 23, 24, 25, 26, 27, 28, 29};      // Vector to Test
    int test_array[length] {20, 21, 22, 23, 24, 25, 26, 27, 28, 29};        // Ground Truth c-array to test against

    // Vector capacity is not garunteed to be the same as the number of elements. Shrink to fit for test. 
    vec.shrink_to_fit(); 

    // Data returns a pointer to firt element of the private _array inside the Array class
    int* raw_arr_ptr = vec.data();    
    EXPECT_NE(raw_arr_ptr, nullptr);        // Pointer Shouldnt not be empty

    // Iterator through every element of the array and test that the ground truth and array values match
    for(int idx =0; idx < length; idx++ )
    {
        int true_val = test_array[idx];
        int test_val = *(raw_arr_ptr + idx);
        EXPECT_EQ(true_val, test_val);
    }
    
}

TEST(TestVectorPublicMethods, TestVectorSwapMethod) {

    const size_t length = 10;
    Vector<int> vector_1 {1,2,3,4,5,6,7,8,9,10};
    Vector<int> vector_2 {11,12,13,14,15,16,17,18,19,20};

    // Test that array values are NOT the same 
    for (int idx = 0; idx < length; idx++) { EXPECT_NE(vector_1[idx], vector_2[idx]); }

    // Swap The contents of Array2 into Array1 
    vector_1.swap(vector_2);

    // Test that array values ARE the same 
    for (int idx = 0; idx < length; idx++) { EXPECT_EQ(vector_1[idx], vector_2[idx]); }
}

class DummyClass
{
    public: 
    DummyClass() = default;
    DummyClass(float my_float, char my_char, int my_int, std::string my_string) :
    my_float{my_float}, my_char{my_char}, my_int{my_int}, my_string{my_string} {}

    void print()
    {
        std::cout << "INT: " << my_int << "CHAR: " << my_char << "FLOAT: " << my_float  << "STRING: " << my_string << std::endl;
    } 

        float my_float;
        char my_char;
        int my_int; 
        std::string my_string; 
};


// TEST(TestVectorPublicMethods, TestVectorEmplaceBack)
// {
    

//     Vector<int> expected_vector {1,2,3,4,5,6, 7};
//     Vector<int> my_vector {1,2,3,4,5};
//     Vector<DummyClass> my_dummy_vector; 
//     Vector<DummyClass> expect_dummy_vector {DummyClass(1, 'a', 3.14f, "hello"), DummyClass(2, 'b', 2.1728f, "goodbye")}; 


//     // my_vector.emplace_back(6);
//     // my_vector.emplace_back(7);

//     // bool result = (my_vector == expected_vector);

//     // EXPECT_TRUE(result);

//     // // Emplace Back DummyClass (Instantiate New object in emplace operation)
//     // my_dummy_vector.emplace_back(1, 'a', 3.14f, "hello");
//     // my_dummy_vector.emplace_back(2, 'b', 2.1728f, "goodbye");


//     // EXPECT_EQ(my_dummy_vector[0].my_int, expect_dummy_vector[0].my_int);
//     // EXPECT_EQ(my_dummy_vector[0].my_char, expect_dummy_vector[0].my_char);
//     // EXPECT_EQ(my_dummy_vector[0].my_float, expect_dummy_vector[0].my_float);
//     // EXPECT_EQ(my_dummy_vector[0].my_string, expect_dummy_vector[0].my_string);

//     // EXPECT_EQ(my_dummy_vector[1].my_int, expect_dummy_vector[1].my_int);
//     // EXPECT_EQ(my_dummy_vector[1].my_char, expect_dummy_vector[1].my_char);
//     // EXPECT_EQ(my_dummy_vector[1].my_float, expect_dummy_vector[1].my_float);
//     // EXPECT_EQ(my_dummy_vector[1].my_string, expect_dummy_vector[1].my_string);

//     // for(auto element : my_dummy_vector)
//     // {
//     //     // element.print();
//     // }

// }


// TEST(TestVectorPublicMethods, TestVectorAssignMethodFillForceAllocation) {

//     size_t length = 10;
//     size_t new_length = 100;
//     int assign_val = 69; 
//     Vector<int> myVector {1,2,3,4,5,6,7,8,9,10};

//     EXPECT_EQ(myVector.size(), length);

//     for(auto p : myVector) 
//     {     
//         EXPECT_NE(p,assign_val);  
//     }

//     myVector.assign(new_length, assign_val);

//     EXPECT_EQ(myVector.size(), new_length);

//     for(auto it = myVector.begin(); it != myVector.end(); ++it) 
//     {     
//         // std::cout << p << std::endl;
//         EXPECT_EQ( *it, assign_val);  
//     }
// }

// TEST(TestVectorPublicMethods, TestVectorAssignMethodFillNoForceAllocation) {

//     size_t length = 10;
//     size_t new_length = 6;
//     int assign_val = 69; 
//     Vector<int> myVector {1,2,3,4,5,6,7,8,9,10};

//     EXPECT_EQ(myVector.size(), length);

//     for(auto p : myVector) 
//     {     
//         EXPECT_NE(p,assign_val);  
//     }

//     myVector.assign(new_length, assign_val);

//     EXPECT_EQ(myVector.size(), new_length);

//     for(auto it = myVector.begin(); it != myVector.end(); ++it) 
//     {     
//         // std::cout << p << std::endl;
//         EXPECT_EQ( *it, assign_val);  
//     }
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





















































































































































































































































// // TEST(TestVectorIterators, TestIteratorAssignmentOperation) {

// //     structures::Vector<int> my_vect(5, 99);
// //     my_vect.Print();
// //     EXPECT_TRUE(true);
// // }



// TEST(TestVector, TestVectorPrint) {

//     structures::Vector<int> my_vect;

//     for(int i =0; i <5 ; i++)
//     {
//         my_vect.push_back(i);
//     }
    
//     my_vect.Print();

//     EXPECT_TRUE(true);
// }

// // TEST(TestVectorConstructors, TestLengthConstructors) {

// //     structures::Vector<int> my_vect(5);
// //     my_vect.Print();
// //     EXPECT_TRUE(true);
// // }

// TEST(TestVectorConstructors, TestLengthFillConstructors) {

//     structures::Vector<int> my_vect(5, 99);
//     my_vect.Print();
//     EXPECT_TRUE(true);
// }

// TEST(TestVectorElementAccess, TestIndexOperatorOverload) {

//     structures::Vector<int> my_vect(5, 420);
//     int output = my_vect[4];

//     std::cout << "My My Vector Output Val = " << output << std::endl;
//     EXPECT_TRUE(true);
// }

// TEST(TestVectorElementAccess, TestDataMethod) {

//     structures::Vector<int> my_vect(5, 420);
//     int* my_data = my_vect.data();

//     for(int i =0; i < 5 ; i++)
//     {
//         std::cout << "My My Vector Output Val at index: " << i <<  " = " << my_data[i] << std::endl;
//     }

//     EXPECT_TRUE(true);
// }


// // TEST(TestVectorConstructors, TestRangeConstructors) {

// //     std::array<int, 5> arr;
// //     arr.fill(69);

// //     structures::Vector<int> my_vect(arr.begin(), arr.end());
    
// //     my_vect.Print();

// //     EXPECT_TRUE(true);
// // }



// /*
//  * Test Public Methods
//  */

// // TEST(TestDynamicArrayMethods, TestArrayDefaultConstructor) {
// //     EXPECT_TRUE(true);
// // }

// // TEST(TestDynamicArrayMethods, TestEmptyMethod) {

// // }

// // TEST(TestDynamicArrayMethods, TestSizeMethod) {

// // }

// // TEST(TestDynamicArrayMethods, TestCapacityMethod) {

// // }

// // TEST(TestDynamicArrayMethods, TestShrinkToFitMethod) {

// // }

// // TEST(TestDynamicArrayMethods, TestClearMethod) {

// // }

// // TEST(TestDynamicArrayMethods, TestPushBackMethod) {

// // }

// // TEST(TestDynamicArrayMethods, TestPopBackMethod) {

// // }

// // TEST(TestDynamicArrayMethods, TestResizeMethod) {

// // }

// // TEST(TestDynamicArrayMethods, TestAtMethod) {

// // }


// // /*
// //  * Test Iterator
// //  */

// // TEST(TestDynamicArrayIterators, TestIteratorFront) {

// // }

// // TEST(TestDynamicArrayIterators, TestIteratorBack) {

// // }

// // TEST(TestDynamicArrayIterators, TestForwardIteration) {

// // }

// // TEST(TestDynamicArrayIterators, TestReverseIteration) {

// // }
