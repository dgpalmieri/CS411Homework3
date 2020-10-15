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

enum{ GCS, NOFIRST, NOLAST, SUM };

void printVector(const std::vector<int> & vec){// TODO: Remove me
    cout << "{ ";
    for ( const auto & i: vec )
        cout << i << " ";
    cout << "}" << endl;
}

template<typename RAIter>
std::vector<int> recurse( RAIter first, RAIter last ){

    cout << "sequence: "; // TODO: Remove me
    for ( auto i = first; i != last; ++i )
        cout << *i << " ";
    cout << endl;

    std::vector<int> callOne, callTwo, values{ 0, 0, 0, 0 };
    int dist = std::distance( first, last ); 
    bool pos = true, even = dist % 2 == 1;

    for ( auto i = first + 1; i != last; ++i ){
        values[NOFIRST] += *i;
    }
    for ( auto i = first; i != last - 1; ++i ){
        values[NOLAST] += *i;
    }
    for ( auto i = first; i != last; ++i ){
        values[SUM] += *i;
        if ( *i < 0 ) { pos = false; }
    }

    for ( auto & i : values ){
        if ( i < 0 ){
            i = 0;
        }
    }

    dist = dist/2;

    if ( first != last && dist != 0 ){
        cout << "CALL ONE" << endl;
        callOne = recurse( first, last - dist );
        cout << "EXITED STACK FRAME" << endl;// TODO: Remove me
        if ( first + dist + 1 != last ){
            cout << "dist: " << dist << endl;// TODO: Remove me
            cout << "CALL TWO" << endl;// TODO: Remove me
            if ( even ) {
                callTwo = recurse( first + dist + 1, last );
            } else {
                callTwo = recurse( first + dist, last );
            }
            cout << "EXITED STACK FRAME" << endl;// TODO: Remove me
        } else {
            cout << "CALL TWO - NR" << endl;// TODO: Remove me
            callTwo = std::vector<int>{ std::max( *( last - 1 ), 0 ), 0, 0, 0 };
        }
    } else { cout << "SINGLE VALUE" << endl; return { *first, 0, 0, 0 }; }

    for ( const auto & i : values ) {
        if ( i > values[GCS] )
            values[GCS] = i;
    }
    cout << "sequence: "; // TODO: Remove me
    for ( auto i = first; i != last; ++i )
        cout << *i << " ";
    cout << endl;

    cout << "values vector: ";
    printVector(values);// TODO: Remove me
    cout << "CallOne vector: ";
    printVector(callOne);
    cout << "CallTwo vector: ";
    printVector(callTwo);

    values[GCS] = std::max(  std::max( callOne[GCS], callTwo[GCS] ), values[GCS]);
    cout << "Current GCS: " << values[GCS] << endl;// TODO: Remove me

    cout << "values II vector: ";
    printVector(values);// TODO: Remove me

    values[GCS] = std::max( std::max( std::max( values[NOFIRST], values[NOLAST] ),
                  values[GCS] ),
                  callOne[NOLAST] + callTwo[NOFIRST]);

    cout << "values III vector: ";
    printVector(values);// TODO: Remove me


    return values;
}

template<typename RAIter>
int contigSum( RAIter first, RAIter last ){
    cout << endl << endl; // TODO: Remove Me
    bool positive = false;

    if ( first == last ) { return 0; }
    for( auto iter = first; iter != last; ++iter ){
        if ( *iter > 0 ) { positive = true; break; }
    }
    if ( !positive ) { return 0; }

    if ( first == last - 1 ) { return *first; }

    std::vector<int> sum = recurse( first, last );

    cout << "Returning: " << sum[0] << endl;

    return sum[0]; 
}

#endif /* CONTIGSUM_HPP */
