#include "Set.h"





Set::Set() {
	m_numberItems = 0;
	
	
}

bool Set::empty() const {
	if (m_numberItems == 0)
		return true;
	else
		return false;
}

int Set::size() const {
	return m_numberItems;
}

bool Set::insert(const ItemType& value) {
	int index = 0;
	int dupCount = 0;
	bool insert = false;
	ItemType temp;
	int elementCount = 0;
	if (m_numberItems == 150) {
		return false;
	}
	else {
		if (m_numberItems == 0) {
			elementCount = m_numberItems + 1;
		}
		else {
			elementCount = m_numberItems;
		}

		
		for (int i = 0; i != elementCount; i++) {
			index++;
			//not sure what size should be
			if (value == m_setarray[i]) {
				dupCount++;
			}
		}
		if (dupCount >= 1) {
			insert = false;
		}
		else {
			insert = true;
			if (m_numberItems == 0) {
				m_setarray[0] = value;
			}
			else {
				m_setarray[index] = value;
			}
			m_numberItems += 1;
			for (int i=0;i!=m_numberItems;i++)
				for (int j=i+1; j!=m_numberItems;j++)
					if (m_setarray[i] < m_setarray[j]) {
						temp = m_setarray[i];
						m_setarray[i] = m_setarray[j];
						m_setarray[j] = temp;
					}



		}

		
	}return insert;

	



}

bool Set::erase(const ItemType& value) { //set to empty string?


	bool erase = false;
	int i;
	for (i = 0; i < m_numberItems; i++) {
		if (m_setarray[i] == value) {

			erase = true;
			//m_numberItems--;
			break;
		}


	}if (i < m_numberItems) {
		m_numberItems -= 1;
		//elementCount--;
		for (int j = i; j != m_numberItems; j++) {
			m_setarray[j] = m_setarray[j + 1]; //turns index after element count into  //do std remove?
		}



		
	}
	return erase;
}
	




bool Set::contains(const ItemType& value) const  {
	//how to find number of elements?
	int elementCount = 0;
	bool contain = false;
	if (m_numberItems == 0) {
		elementCount = 1;
	}
	else {
		elementCount = m_numberItems;
	}
	for (int i = 0; i != elementCount; i++) {
		if (value == m_setarray[i]) {
			contain = true;
			break;
		}
	}return contain;
}

bool Set::get(int i, ItemType& value) const {
	if (i<0 || i>=m_numberItems || m_numberItems == 0)
		return false;
	else {
		value = m_setarray[i];
		return true;

	}
}


void Set::swap(Set& other) {
	int temp = m_numberItems;
	m_numberItems = other.m_numberItems;
	other.m_numberItems = temp;

	


	if (other.m_numberItems > m_numberItems) {
		for (int p = 0; p != other.m_numberItems; p++) {
			ItemType p2 = m_setarray[p];
			m_setarray[p] = other.m_setarray[p];
			other.m_setarray[p] = p2;
		}
	}
	else
	{
		for (int p = 0; p !=m_numberItems; p++) {
			ItemType p2 = m_setarray[p];
			m_setarray[p] = other.m_setarray[p];
			other.m_setarray[p] = p2;
		}

	}
}
	

	
	


	

	

	

