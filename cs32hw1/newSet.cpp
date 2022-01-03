#include "newSet.h"
#include <iostream>
#include <cstdlib>


Set::Set() {
	m_numberItems=0;
	//m_size = 0;
	m_maxSize = 150;
	//m_setarray[DEFAULT_MAX_ITEMS];
	m_setarray = new ItemType[DEFAULT_MAX_ITEMS];

}

Set::Set(int storage) {
	if (storage < 0) {
		std::cout << "Error! Array size can't be negative" << std::endl;
		exit(1);
	}
	else {
		
		m_maxSize = storage;
		m_numberItems = 0;
		//m_size = 0;
		m_setarray = new ItemType [m_maxSize];
	}
}


Set::Set(const Set& other) /*: m_numberItems(other.m_numberItems), m_storage(other.m_storage)*/  {
	m_numberItems = other.m_numberItems;
	m_maxSize = other.m_maxSize;
	m_setarray = new ItemType[m_maxSize];
	for (int i = 0; i < m_maxSize;i++) {
		m_setarray[i] = other.m_setarray[i];
	}
	
	
}


Set::~Set() {
	delete [] m_setarray;
}

Set& Set::operator=(const Set& ms) {
	if (this != &ms) {
		Set temp(ms);
		swap(temp);
	}
	return *this;
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
	
	if (m_numberItems == m_maxSize) {
		return false;
	}
	else
	 {
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
			
			
				for (int i = 0;i != m_numberItems;i++)
					for (int j = i + 1; j != m_numberItems;j++)
						if (m_setarray[i] < m_setarray[j]) {
							temp = m_setarray[i];
							m_setarray[i] = m_setarray[j];
							m_setarray[j] = temp;
						
						}
			


		
		}
		


	}
	return insert;





}







bool Set::erase(const ItemType& value) { //set to empty string?


	bool erase = false;
	int i;
	for (i = 0; i != m_numberItems; i++) {
		if (value == m_setarray[i]) {

			erase = true;
			//m_numberItems--;
			break;
		}


	}if (i < m_numberItems) {
		m_numberItems--;
		//elementCount--;
		for (int j = i; j < m_numberItems; j++) {
			m_setarray[j] = m_setarray[j + 1]; //turns index after element count into  //do std remove?
		}
		//std::remove(0, m_numberItems-1, value);
	}
	return erase;
}



bool Set::contains(const ItemType& value) const {
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
	if (i<0 || i>=m_numberItems || m_numberItems==0)
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
	
	int temp2 = m_maxSize;
	m_maxSize = other.m_maxSize;
	other.m_maxSize = temp2;


	ItemType* temp3 = m_setarray;
	m_setarray = other.m_setarray;
	other.m_setarray = temp3;

	//ItemType* set1 = m_setarray;
	//ItemType* set2 = other.m_setarray;

	//ItemType* temp2 = m_setarray;
	//*m_setarray = *other.m_setarray;
	//*other.m_setarray = *temp2;
	//set1 = set2;
	//set2 = temp2;

	//std::swap(m_setarray, other.m_setarray);


}

