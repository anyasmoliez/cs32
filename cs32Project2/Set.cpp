#include "Set.h"
#include <iostream>

Set::Set() {
	head = new Node;
	head->next = head;   //initializes head to point to itself
	head->prev = head;
	m_size = 0;
	
	

}

Set::~Set() { 
	
	for (int i = 0; i != m_size; i++) {
		Node* p = head->next;              //p points to head's next
		head->next = p->next;               
		head->prev = p->prev;                
		delete p;                            //deletes each p node
	}
	delete head;
}

Set& Set:: operator=(const Set& rhs) {
	if (this != &rhs) {
		
		Set temp(rhs);          //call copy constructor and swap sets
		swap(temp);
	}
	return *this;
}

Set::Set(const Set& other):m_size(other.m_size) {
	
	head = new Node;                 //head points to itself initially
	head->next = head;
	head->prev = head;
	
	for (Node* p = other.head->next; p != other.head;p=p->next) {
		Node* t = new Node;                         //create new nodes and copy value of other node into new node
		t->value = p->value;
		t->next = head;                             //asigns new node's next to point to head
		t->prev = head->prev;                       //links nodes together
		t->prev->next = t;                           
		t->next->prev = t;                            
		
		
		
	}
	
	
	

}

bool Set::empty() const {
	if (m_size == 0) {
		return true;
	}
	else
		return false;
}

int Set::size() const {
	
	
	return m_size;


}

bool Set::insert(const ItemType& value) {
	bool insert = false;
	
	
	if (m_size == 0) {
		Node* newNode = new Node();    //creates new Node and assigns value into new node if list is empty
		Node* p = head;
		newNode->value = value;
		
		newNode->next = p->next;       //links newNode to head
		p->next = newNode;             // 
		newNode->prev = p->prev;        
		p->prev = newNode;              
		
		
		m_size += 1;
		return true;

	}
	else {
		Node* p;
		for (p = head->next;p != head;p = p->next) {
			if (p->value == value) {
				return false;
			}
		}
		for (p = head->next;p != head;p = p->next) {
			if (p->value < value) {   //if current value of node is less than the value to be inserted, exit the loop
				
				break;
			}


		}
		Node* newGuy = new Node();   //sort the linked list from descending order and create new node for the value to be inserted
		newGuy->value = value;
		newGuy->prev = p->prev;        
		newGuy->next = p;
		
		p->prev->next = newGuy;
		p->prev = newGuy;
		
		
		insert = true;
		m_size += 1;
		

	}

	
	return insert;
}

bool Set::erase(const ItemType& value) {
	bool erase = false;
	for (Node* p = head->next;p != head; p = p->next) {
		if (p->value == value) {            //if value is found, re-link the nodes to connect without the node with the value
			p->prev->next = p->next;         
			                                 
			p->next->prev = p->prev;         
			delete p;                       // delete the node with the value
			
			m_size--;
			
			erase = true;
			break;
		}



	}return erase;
}

bool Set::contains(const ItemType& value) const {
	bool contains = false;
	for (Node* p = head->next;p != head;p = p->next) {
		if (p->value == value) {
			contains = true;
		}
	}
	return contains;
}

bool Set::get(int pos, ItemType& value) const {
	if (pos<0 || pos >= m_size) {
		return false;
	}
	else {
		Node* p = head->next;
		for (int i = 0; i < pos;i++) { 

			p = p->next;            //update where p points to while i < pos
			
			if (i+1 == pos)
				break;
		}
		value = p->value;   //set value equal to value that pointer points to
	}
	return true;
}

void Set::swap(Set& other) {
	int temp = m_size;
	m_size = other.m_size;      //swap size of both sets
	other.m_size = temp;

	Node* temp2 = head;          //swap head pointers of both sets
	head = other.head;
	other.head = temp2;

}


void Set::dump() const {
	//Node* p = head->next;
	for (Node* p = head->next;p != head;p = p->next) {
		std::cerr << p->value << std::endl;
	}
	
}

void unite(const Set& s1, const Set& s2, Set& result) {
	Set temp;
	for (int i = 0; i != s1.size();i++) {
		ItemType x;
		s1.get(i, x);
		temp.insert(x);                   //gets each value of s1 and inserts into temp
	}
	for (int i = 0; i != s2.size(); i++) {
		ItemType x;
		s2.get(i, x);
		temp.insert(x);                   //gets each value of s2 and inserts into temp
	}
	result = temp;                         //assign result to equal temp

}
void difference(const Set& s1, const Set& s2, Set& result) {
	unite(s1, s2, result);                    //unite s1 and s2
	Set temp;
	for (int i = 0; i < result.size(); i++) {
		ItemType x;
		result.get(i, x);
		temp.insert(x);                        //get each value of result and insert into temp
		if (s1.contains(x) && s2.contains(x)) {  //if s1 and s2 contain value, erase it in temp
			temp.erase(x);
		}
	}
	result = temp;                                 //assign result to temp
	
}