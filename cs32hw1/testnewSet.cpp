#include "newSet.h"
#include <cassert>
#include <iostream>
using namespace std;




int main() {
    

     


    Set aa(1000);   // a can hold at most 1000 distinct items
    Set bb(5);      // b can hold at most 5 distinct items
    Set cc;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    ItemType v[6] = {"h","e", "i", "k", "s", "t"};

    // No failures inserting 5 distinct items into b
    for (int k = 0; k < 5; k++)
        assert(bb.insert(v[k]));

    // Failure if we try to insert a sixth distinct item into b
    assert(!bb.insert(v[5]));

    // When two Sets' contents are swapped, their capacities are swapped
    // as well:
    aa.swap(bb);
    assert(!aa.insert(v[5]) && bb.insert(v[5]));


    Set d(4);
    d.insert("h");
    d.insert("i");
    d.insert("y");
    d.insert("s");

    Set e(2);
    e.insert("x");
    e.insert("t");

    d = e;
    
    
   


    
    std::cerr << "ya"; 



}
