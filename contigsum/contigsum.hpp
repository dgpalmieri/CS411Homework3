// contigsum.hpp
// Dylan Palmieri
// 2020-10-14
// Header containing contiguous subset sum template function

#ifndef CONTIGSUM_HPP
#define CONTIGSUM_HPP

#include<iterator>
#include<numeric>
#include<vector>

#include<iostream> // For Debugging, remove in production
using std::cout;
using std::endl;

enum{ GCS, NOFIRST, NOLAST, SUM };

template<typename RAIter>
std::vector<int> recurse( RAIter first, RAIter last ){
    bool even;
    std::vector<int> callOne, callTwo, values{ 0, 0, 0, 0 };
    std::vector<int> zeroes(values);
    int dist = std::distance( first, last ); 

    for ( auto i = first + 1; i != last; ++i ){
        values[NOFIRST] += *i;
    }
    for ( auto i = first; i != last - 1; ++i ){
        values[NOLAST] += *i;
    }

    if ( values[NOFIRST] < 0 ){ values[NOFIRST] = 0; }
    if ( values[NOLAST] < 0 ){ values[NOLAST] = 0; }

    if ( first != last ){
        dist = dist/2;
        callOne = recurse( first, last - dist - 1 );
        callTwo = recurse( first + dist + 1, last );
    } else { return zeroes; }

    return values;
}

template<typename RAIter>
int contigSum( RAIter first, RAIter last ){
    bool positive = false;

    if ( first == last ) { return 0; }
    for( auto iter = first; iter != last; ++iter ){
        if ( *iter > 0 ) { positive = true; }
    }
    if ( !positive ) { return 0; }

    if ( first == last - 1 ) { return *first; }

    std::vector<int> sum = recurse( first, last );

    return sum[0]; 
}

#endif /* CONTIGSUM_HPP */
