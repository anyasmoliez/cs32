#include "AccountSet.h"
#include <cassert>
#include <iostream>
using namespace std;

int main() {

	AccountSet s;
	s.add(123456789);
	s.add(234567891);
	s.add(123456789);
	assert(s.size() == 2);
	s.print();
	AccountSet a;
	assert(a.size() == 0);
	a.add(123);
	a.add(124);
	a.add(124);
	a.add(125);
	assert(a.size() == 3);
	a.print();

	cerr << "yay";



}