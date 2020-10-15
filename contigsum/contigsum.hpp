// contigsum.hpp
// Dylan Palmieri
// 2020-10-14
// Header containing contiguous subset sum template function

#ifndef CONTIGSUM_HPP
#define CONTIGSUM_HPP

int recurse(RAIter first, RAIter last){
    int dist = std::distance(first, last); 

    return 0;
}

template<typename RAIter>
int contigSum(RAIter first, RAIter last){
    if (first == last) { return 0; }

    int sum = recurse(first, last);

    return sum;
}

#endif /* CONTIGSUM_HPP */
