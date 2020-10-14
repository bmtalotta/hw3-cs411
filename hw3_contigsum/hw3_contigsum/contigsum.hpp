//contigsum.hpp
//**********************************************
//heavily modified version of merge_sort.cpp
// Glenn G. Chappell
// 9 Oct 2015
//
// For CS 411/611 Fall 2015
// Merge Sort using Iterators
//**********************************************
//Ben Talotta
//10/13/2020
//for use in cs411 hw 3 exercise A

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;
#include <algorithm>
using std::copy;
#include <iterator>
using std::distance;
using std::advance;
#include <type_traits>
using std::remove_reference;

#ifndef contigsum_HPP
#define contigsum_HPP
int max(int left, int right) {
    if (left > right) {
        return left;
    }
    else {
        return right;
    }
};
int max(int left, int right, int total) {
    return max(max(left, right), total);
};

template<typename RAIter>
int CrossContigSum(RAIter first, RAIter middle, RAIter last) {
    int sum = 0;
    int leftSum = -99999; //dummy val to be overwritten later
    for (auto i = first; i < middle; i++) {
        sum += *i;
        if (sum > leftSum) {
            leftSum = sum;
        }
    }
    int rightSum = -99999; //dummy val to be overwritten later
    sum = 0;
    for (auto i = middle; i < last; i++) {
        sum += *i;
        if (sum > rightSum) {
            rightSum = sum;
        }
    }
    int total = leftSum + rightSum;
    return max(leftSum, rightSum, total);
};
template<typename RAIter>
int contigSum(RAIter first, RAIter last)
{
    size_t size = distance(first, last);
    if (size == 0) {
        return 0;
    }
    if (size == 1) {
        if (*first > 0) {
            return *first;
        }
        else
            return 0;
    }
    // RECURSIVE CASE
    RAIter middle = first;
    advance(middle, size / 2);  // middle is iterator to middle of range
    contigSum(first, middle);
    contigSum(middle, last);
    return max(contigSum(first,middle), contigSum(middle, last), CrossContigSum(first, middle, last));
};

#endif "!contigsum_HPP"
