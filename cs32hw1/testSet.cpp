#include "Set.h"
#include <iostream>
#include <cassert>
#include <string>
using namespace std;




int main()
{
    Set s;
    Set a;
    assert(s.empty());
    assert(s.size() == 0);
    s.insert("hello");
    assert(!s.contains("hi"));
    s.insert("bye");
    a.insert("hi");
    a.insert("yo");
    assert(a.size() == 2);
    s.swap(a);
    assert(s.size() == 2 && s.contains("hi") && s.contains("yo"));
    assert(a.size() == 2 && a.contains("hello") && a.contains("bye"));
    a.insert("hello");
    assert(a.size() == 2);
    a.insert("cool");
    a.insert("awesome");
    a.insert("fun");
    a.erase("fun");
    assert(a.size() == 4);
    ItemType x;
    assert(!a.get(5, x));
    //a.get(3, x);
    //assert(x == "awesome"); 

 

    

    cerr << "yay";
}

