

bool allTrue(const string a[], int n) { //change this
	if (n <= 0) {
		return true;
	}
	if (n != 0) {
		if (!somePredicate(a[n - 1])) {
			return false;
		}
		
	}
	return allTrue(a,n-1);
}

int countFalse(const string a[], int n) {
	
	if (n <= 0)
		return 0;

	else{
	
		if (!somePredicate(a[n - 1]))
			return 1+countFalse(a,n-1);
		
			
	}
	return countFalse(a, n - 1);
}

int firstFalse(const string a[], int n) {
	
	if (n <= 0)
		return -1;
	 if (!somePredicate(a[0]))
		return 0;
	int index = firstFalse(a + 1, n - 1);
	 
		



		if (index<0)
			return  -1;




	
	
		return index+1;
}

int indexOfLeast(const string a[], int n) {
	if (n <= 0)
		return -1;
	 if (n == 1)
		return 0;
	int k = indexOfLeast(a+1, n - 1)+1;
	if (a[0] < a[k])
		return 0;
	else
		return k;
	
	
}

bool includes(const string a1[], int n1, const string a2[], int n2) {
	if (n2 <= 0)
		return true;
	if (n1<=0 && n2 <= 0)
		return true;
	if (n1 < n2)
		return false;

	
	
		
	if (a1[n1 - 1] == a2[n2 - 1])
		return includes(a1,n1-1,a2,n2-1);
	else
		return includes(a1, n1 - 1, a2, n2);
			
	
	 



}