// inversions.hpp
// Dylan Palmieri
// 2020-10-14
// Header containing inversions template function

#ifndef CONTIGSUM_HPP
#define CONTIGSUM_HPP

// Changes to the original mergesort file will be denoted
// using a comment on the same line, beginning with "CHANGED - ",
// and a short description of what was changed
// Ex) ... // CHANGED - Added this line

// ********************* FROM merge_sort.cpp, by G.G. Chappell *********************

#include <iostream>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <iterator>
#include <type_traits>
#include<iterator>


// stableMerge
// Merge two halves of a sequence, each sorted, into a single sorted
// sequence in the same location. Merge is done in a stable manner.
// Requirements on Types:
//     FDIter is a forward iterator type.
//     The value type of FDIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, middle) and [middle, last) are valid ranges, each sorted
//      by <.
// Post:
//     [first, last) contains the same items as it did initially, but
//      now sorted by < (in a stable manner).
template <typename FDIter>
int stableMerge(FDIter first, FDIter middle, FDIter last) // CHANGED - return type void is now int
{
    // ** C++03:
    using Value = typename std::iterator_traits<FDIter>::value_type;
    // ** C++11:
//    using Value = typename remove_reference<decltype(*first)>::type;
    // ** Is this really better?

    std::vector<Value> buffer(distance(first, last));
                                // Buffer for temporary copy of data
    FDIter in1 = first;         // Read location in 1st half
    FDIter in2 = middle;        // Read location in 2nd half
    auto out = buffer.begin();  // Write location in buffer
    // ** auto! That *is* better than vector<Value>::iterator

    std::size_t inversions = 0; // CHANGED - Added this line

    // Merge two sorted lists into a single list in buff.
    while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1)  // Must do comparison this way, to be stable.
            *out++ = *in2++;
        else
            *out++ = *in1++;
    }

    // Copy remainder of original sequence to buffer.
    // Only one of the following two copy calls will do anything, since
    //  the other is given an empty source range.
    copy(in1, middle, out);
    copy(in2, last, out);

    // Copy buffer contents back to original sequence location.
    copy(buffer.begin(), buffer.end(), first);

    return inversions; // CHANGED - Added this line
}


// mergeSort
// Sorts a sequence, using Merge Sort.
// Recursive.
// Requirements on Types:
//     FDIter is a forward iterator type.
//     The value type of FDIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, last) is a valid range.
// Post:
//     [first, last) contains the same items as it did initially,
//      but now sorted by < (in a stable manner).
template <typename FDIter>
int mergeSort(FDIter first, FDIter last) // CHANGED - return type void is now int
{
    // Compute size of sequence
    std::size_t size = std::distance(first, last);

    // BASE CASE
    if (size <= 1)
        return 0;

    // RECURSIVE CASE
    FDIter middle = first;
    std::advance(middle, size/2);  // middle is iterator to middle of range

    // Recursively sort the two lists
    mergeSort(first, middle);
    mergeSort(middle, last);

    // And merge them
    return stableMerge(first, middle, last); // CHANGED - Added "return" to beginning of line
}

// ********************* MERGE_SORT.CPP ENDS *********************

template<typename RAIter>
std::size_t inversions(RAIter first, RAIter last){
    return mergeSort(first, last);
}

#endif /* CONTIGSUM_HPP */
