// contigsum.hpp
// Dylan Palmieri
// 2020-10-14
// Header containing contiguous subset sum template function

#ifndef CONTIGSUM_HPP
#define CONTIGSUM_HPP

#include<iterator>
#include<numeric>
#include<vector>
#include<algorithm>

#include<iostream> // For Debugging, remove in production
using std::cout;
using std::endl;

enum{ A, B, C, D };

void printVector(const std::vector<int> & vec){// TODO: Remove me
    cout << "{ ";
    for ( const auto & i: vec )
        cout << i << " ";
    cout << "}" << endl;
}

template<typename RAIter>
std::vector<int> recurse( RAIter first, RAIter last ){

    std::vector<int> left( 5, 0 ), right( 5, 0 ), values( 5, 0 );
    std::size_t size = std::distance( first, last ); 

    // RECURSIVE CASE
    if ( size > 1 ){
        auto middle = first;
        middle += size/2;

        left = recurse(first, middle);
        right = recurse(middle, last);
    }
    else { // BASE CASE, size = 0;
        return { *first, *first, *first, *first };
    }

    values[D] = left[D] + right[D];
    values[C] = std::max( { right[C], right[D] + left[C], values[D] } );
    values[B] = std::max( { left[B], left[D] + right[B], values[D] } );
    values[A] = std::max( { values[B], values[C], values[D],
                            left[A], left[C] + right[B] } );

    return values;
}

template<typename RAIter>
int contigSum( RAIter first, RAIter last ){

    if ( first == last ) { return 0; }

    std::vector<int> sum = recurse( first, last );

    if ( sum[0] < 0 ) { return 0; }

    return sum[0]; 
}

#endif /* CONTIGSUM_HPP */
