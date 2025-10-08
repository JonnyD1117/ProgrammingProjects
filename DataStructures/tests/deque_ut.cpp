#include <gtest/gtest.h>
#include "deque.hpp"
#include <iostream>

using namespace structures;

// template<typename T, typename... Args>
// Vector<T> build_vector(Args &&... args)
// {
//     Vector<T> test_vector {args...};

//     return test_vector;
// } 

// template <typename T>
// void print_vector(Vector<T>& vector)
// {   
//     for(auto iter = vector.begin(); iter != vector.end(); iter++)
//     {
//         std::cout<< *iter << std::endl;
//     }
// }

TEST(TestDeque, DequeCreation)
{

    Block<int> blk; 

    blk.push_back(1);
    blk.push_back(2);
    blk.push_back(3);
    blk.push_back(4);
    blk.push_back(5);


    for (size_t idx = 0; idx < 5; ++idx)
    {
        std::cout << blk.pop_back() << std::endl;
    }


    // Vector<int> vec = build_vector<int>(0, 1,2,3,4,5,6,7,8,9);

    // for(int idx =0 ; idx < 10; idx++)
    // {
    //     EXPECT_EQ(vec[idx], idx);
    // }

    // EXPECT_TRUE(true);
}