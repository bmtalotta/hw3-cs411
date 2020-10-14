//inversions.hpp
//**********************************************
//modified version of merge_sort.cpp
// Glenn G. Chappell
// 9 Oct 2015
//
// For CS 411/611 Fall 2015
// Merge Sort using Iterators
//**********************************************
//Ben Talotta
//10/13/2020
//for use in cs411 hw 3 exercise B

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

#ifndef inversions_HPP
#define inversions_HPP

template <typename FDIter>
void stableMerge(FDIter first, FDIter middle, FDIter last, size_t &moveCount)
{
    // ** C++03:
    using Value = typename std::iterator_traits<FDIter>::value_type;
    vector<Value> buffer(distance(first, last));
    // Buffer for temporary copy of data
    FDIter in1 = first;         // Read location in 1st half
    FDIter in2 = middle;        // Read location in 2nd half
    auto out = buffer.begin();  // Write location in buffer
    // Merge two sorted lists into a single list in buff.
    while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1) {  // Must do comparison this way, to be stable.
            *out++ = *in2++;
            moveCount += (middle - in1);
          //  cout << moveCount << "\n";
        }
        else {
            *out++ = *in1++;
        }
    }
    copy(in1, middle, out);
    copy(in2, last, out);
    copy(buffer.begin(), buffer.end(), first);
};
template<typename FDIter>
size_t inversions(FDIter first, FDIter last)
{
    size_t moveCount = 0;
    size_t size = last - first;
    // Compute size of sequence
    if (size <= 1)
        return 0;
    FDIter middle = first;
    advance(middle, size / 2);  // middle is iterator to middle of range
    // Recursively sort the two lists
    moveCount += inversions(first, middle);
    moveCount += inversions(middle, last);
    
    // And merge them
    stableMerge(first, middle, last, moveCount);
    //cout << "at end " << moveCount << "\n";
    return moveCount;
};

#endif "!inversions_HPP"
