//contigsum.hpp
//Ben Talotta
//10/13/2020
//for use in cs411 hw 3 exercise A
#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;
#include <iterator>
using std::distance;
using std::advance;

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
/* psuedo code guidline I used for creating the function
   Divide the given array in two halves
   Return the maximum of following three
    .a) Maximum subarray sum in left half (Make a recursive call)
    .b) Maximum subarray sum in right half (Make a recursive call)
    .c) Maximum subarray sum such that the subarray crosses the midpoint*/
template<typename RAIter>
int CrossContigSum(RAIter first, RAIter middle, RAIter last) {
    int sum = 0;
    int leftSum = 0;
    for (RAIter i = middle; i > first; i--) {
        sum += *i;
        if (sum > leftSum) {
            leftSum = sum;
        }
    }
    //the for loop gets angry if going to I>= first so this is the work around
    sum += *first;
    if (sum > leftSum) {
        leftSum = sum;
    }
    int rightSum = 0;
    sum = 0;
    for (RAIter j = middle+1; j < last; j++) {
        sum += *j;
        if (sum > rightSum) {
            rightSum = sum;
        }
    }
    int total = leftSum + rightSum;
    return max(leftSum,max(rightSum,total));
};
template<typename RAIter>
int contigSum(RAIter first, RAIter last)
{
    size_t size = distance(first, last);
    if (size == 0) {
        return 0;
    }
    if (size == 1) {
        if (*first > 0)
            return *first;
        else
            return 0;
    }
    RAIter middle = first;
    advance(middle, size / 2);
    return max(max(contigSum(first, middle), contigSum(middle + 1, last)), CrossContigSum(first, middle, last));;
};

#endif "!contigsum_HPP"
