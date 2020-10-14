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
#include<iostream> //for testing
using std::cout;

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

template<typename RAIter>
int CrossContigSum(RAIter &first, RAIter &middle, RAIter &last) {
    int sum = 0;
    int leftSum = -99999; //dummy val to be overwritten later
   /* for (RAIter i = first; i < middle; i++) {
        sum += *i;
        if (sum > leftSum) {
            leftSum = sum;
        }
    }
    int rightSum = -99999; //dummy val to be overwritten later
    sum = 0;
    for (RAIter j = middle; j < last; j++) {
        sum += *j;
        if (sum > rightSum) {
            rightSum = sum;
        }
    }*/
    if (middle == first || middle == last) {
        return max(max(*first, *last), *first + *last);
    }
    for (RAIter i = middle; i >= first; i--) {
        sum += *i;
        if (sum > leftSum) {
            leftSum = sum;
        }
    }
    int rightSum = -99999; //dummy val to be overwritten later
    sum = 0;
    for (RAIter j = middle + 1; j <= last; j++) {
        sum += *j;
        if (sum > rightSum) {
            rightSum = sum;
        }
    }
    sum = 0;
    int total = leftSum + rightSum;
    return max(max(leftSum, rightSum), total);
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
    int testingAnswer = max(max(contigSum(first, middle), contigSum(middle, last)), CrossContigSum(first, middle, last));
  //cout << testingAnswer << " \n";
    return testingAnswer;
};

#endif "!contigsum_HPP"
