#include "AccountSet.h"
#include <iostream>
using namespace std;

AccountSet::AccountSet() {
	

}


bool AccountSet::add(unsigned long acctNum) {
	//m_s.insert(acctNum);
	if (m_s.insert(acctNum)) {
		m_s.insert(acctNum);
		return true;
	}
	else
		return false;
}

int AccountSet::size() const {
	return m_s.size();
}

void AccountSet::print() const {
	unsigned long x;
	for (int i = 0; i != m_s.size();i++) {
		m_s.get(i, x);
		cout << x << endl;
	}
}
