#include <iostream>
#include <string>
#include <cassert>
using namespace std;

/*
Make Sure to Add the "Notwithstanding" checks (return -1)
DO NOT COMPARE TWO STRING LITERALS  "help" < "hello" (FAQ)
DELETE COUT AND "DELETE" comments
TEST CASE FOR OUT OF BOUNDS !!!!!!
*/


int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);

//DELETE
void printArr(string a[], int n);

int main() {
		//TEST CASES
		//Nonmutating Functions
		string h[8] = { "melania", "kamala", "donald", "tim", "", "doug", "jd", "donald"};
		assert(lookup(h, 7, "doug") == 5); // string is in array
		assert(lookup(h, 3, "jd") == -1); // string is not in array
		assert(lookup(h, 7, "Tim") == -1); // only accept exact match
		assert(lookup(h, 0, "donald") == -1); // 0 elements in array
		assert(lookup(h, -1, "donald") == -1); // n is negative

		string i[8] = { "kamala", "melania", "melania", "donald", "tim", "", "doug", "jd" };
		assert(positionOfMax(i, 8) == 4); // normal input
		assert(positionOfMax(i, 4) == 1); // multiple valid max strings
		assert(positionOfMax(i, 0) == -1); // 0 elements in array
		assert(positionOfMax(i, -1) == -1); // n is negative

		string e[4] = { "donald", "tim", "", "doug" };
		assert(subsequence(i, 8, e, 4) == 3); // normal input
		assert(subsequence(i, 6, e, 3) == 3); // normal input (check loop out of bounds)
		assert(subsequence(h, 7, i, 2) == -1); // no subsequence
		assert(subsequence(h, 8, i, 1) == 1); // multiple matches return lowest index
		assert(subsequence(h, 7, e, 0) == 0); // any subsequence match
		assert(subsequence(h, 0, e, 0) == -1); // 0 element array
		assert(subsequence(h, 0, e, 1) == -1); // 0 element array (not empty subsequence)
		assert(subsequence(h, -1, e, -1) == -1); // n's are negative

		string g[4] = { "melania", "kamala", "jd", "usha" };
		assert(differ(h, 4, g, 4) == 2); // normal input
		assert(differ(h, 2, g, 2) == 2); // same array contents
		assert(differ(h, 3, g, 2) == 2); // differing array lengths
		assert(differ(h, 1, g, 2) == 1); // differing array lengths
		assert(differ(h, 4, g, 0) == 0); // single empty array 
		assert(differ(h, 0, g, 4) == 0); // single empty array 
		assert(differ(h, 0, g, 0) == 0); // both empty array 
		assert(differ(h, -1, g, -1) == -1); // n's are negative

		string d[8] = { "kamala", "kamala", "kamala", "tim", "tim", "jeb", "ryan", "jeb" };
		assert(countRuns(d, 8) == 5); // normal input
		assert(countRuns(d, 3) == 1); // another normal input (checking sequences correctly)
		assert(countRuns(d, 0) == 0); // 0 element array
		assert(countRuns(d, -1) == -1); // n is negative

		//Mutating Functions
		assert(appendToAll(g, 4, "?") == 4 && g[0] == "melania?" && g[3] == "usha?");
		// normal input
		assert(appendToAll(g, 0, "!!") == 0 && g[0] == "melania?" && g[3] == "usha?");
		// 0 element array no modifying
		assert(appendToAll(g, -1, "?") == -1 && g[0] == "melania?" && g[3] == "usha?");
		// n is negative no modifying

	
		assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jd?" && g[3] == "kamala?");
		// normal input
		assert(rotateLeft(e, 4, 0) == 0 && e[0] == "tim" && e[3] == "donald");
		// normal input (check loop out of bounds)
		assert(rotateLeft(e, 4, -1) == -1 && e[0] == "tim" && e[3] == "donald");
		// pos is negative no modifying
		assert(rotateLeft(e, 4, 5) == -1 && e[0] == "tim" && e[3] == "donald");
		// pos is greater than n no modifying
		assert(rotateLeft(e, 0, 3) == -1 && e[0] == "tim" && e[3] == "donald");
		// 0 element array no modifying
		assert(rotateLeft(e, -1, 2) == -1 && e[0] == "tim" && e[3] == "donald");
		// n is negative no modifying

		string f[3] = { "gwen", "jd", "donald" };
		assert(lookupAny(h, 8, f, 3) == 2); // normal input
		assert(lookupAny(h, 8, f, 1) == -1); // normal no match
		assert(lookupAny(h, 8, f, 0) == -1); // 0 element array
		assert(lookupAny(h, 0, f, 3) == -1); // 0 element array
		assert(lookupAny(h, -1, f, -1) == -1); // n's are negative

		assert(flip(f, 3) == 3 && f[0] == "donald" && f[2] == "gwen"); // normal input (odd array)
		assert(flip(d, 8) == 8 && d[0] == "jeb" && d[7] == "kamala"); // normal input (even array)
		assert(flip(f, 0) == 0 && f[0] == "donald" && f[2] == "gwen"); // 0 element array no modifying
		assert(flip(f, -1) == -1 && f[0] == "donald" && f[2] == "gwen"); // n's are negative no modifying
	
		string j[9] = { "melania", "melania", "kamala", "donald", "tim", "", "doug", "jd", "donald"};
		assert(separate(j, 9, "jd") == 4); // normal input
		assert(separate(j, 9, "melania") == 6 && j[7] == "melania"); // multiple equal separator
		assert(separate(j, 9, "donald") == 1 && j[2] == "donald"); // multiple equal separator
		assert(separate(j, 9, "z") == 9); // none after separator
		assert(separate(j, 0, "melania") == 0); // 0 elements 
		assert(separate(j, -1, "tim") == -1); // n is negative


		cout << "All tests succeeded" << endl;

}


int appendToAll(string a[], int n, string value) {
	if (n < 0) {
		return -1;
	}
	// add value to each element
	for (int i = 0; i < n; i++) {
		a[i] += value;
	}
	return n;
}

int lookup(const string a[], int n, string target) {
	if (n < 0) {
		return -1;
	}
	// search for target in each element
	for (int i = 0; i < n; i++) {
		if (a[i] == target) {
			return i;
		}
	}
	return -1;
}

int positionOfMax(const string a[], int n) {
	if (n < 0) {
		return -1;
	}
	// counts elements that are >= current check string
	int maxCounter = 0;
	for (int i = 0; i < n; i++) {
		// Compare each element with every other element
		string currentString = a[i];
		for (int j = 0; j < n; j++) {
			if (!(currentString >= a[j])) {
				maxCounter = 0;
				break;
			}
			maxCounter++;
		}
		// return earliest index satisfying condition
		if (maxCounter == n) {
			return i;
		}
	}
	return -1;
}

int rotateLeft(string a[], int n, int pos) {
	if (n < 0 || pos >= n || pos < 0) {
		return -1;
	}
	if (pos == n - 1) {
		return pos;
	}
	string endString = a[pos];
	
	for (int i = pos; i < n-1; i++) {
		a[i] = a[i + 1];
	}
	a[n - 1] = endString;

	return pos;
}

int countRuns(const string a[], int n) {
	if (n < 0) {
		return -1;
	}
	if (n == 0) {
		return 0;
	}
	int count = 1;
	string prev = a[0];
	for (int i = 0; i < n; i++) {
		string current = a[i];
		if (current != prev) {
			count++;
			prev = current;
		}
	}
	return count;
}

int flip(string a[], int n) {
	if (n < 0) {
		return -1;
	}
	for (int i = 0; i < n/2; i++) {
		string temp = a[i];
		a[i] = a[n - i - 1];
		a[n - i - 1] = temp;
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) {
		return -1;
	}

	int smallArrSize;
	if (n1 >= n2) {
		smallArrSize = n2;
	}
	else {
		smallArrSize = n1;
	}

	for (int i = 0; i < smallArrSize; i++) {
		if (a1[i] != a2[i]) {
			return i;
		}
	}
	return smallArrSize;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n1 <= 0 || n2 < 0) {
		return -1;
	}

	int subSeqIter = 0;
	for (int i = 0; i < n1; i++) {
		if (subSeqIter == n2) {
			return (i - n2);
		}

		if (a1[i] == a2[subSeqIter]) {
			subSeqIter++;
		} else {
			subSeqIter = 0;
		}
	}
	if (subSeqIter == n2) {
		return (n1 - n2);
	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) {
		return -1;
	}
	
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			if (a1[i] == a2[j]) {
				return i;
			}
		}
	}
	return -1;
}

int separate(string a[], int n, string separator) {
	if (n < 0) {
		return -1;
	}
	/*int num*/
	int counter = 0;
	int i = 0;
	while (i < n && counter < n) {
		if (a[i] >= separator) {
			rotateLeft(a, n, i);
			counter++;
		} else {
			i++;
			counter++;
		}
	}
	// Separately sort all a[i] == separator
	int smallestInd = -1; //FIXME: CHECK THIS TEST CASES
	for (i = 0; i < n; i++) {
		if (a[i] >= separator) {
			smallestInd = i;
			break;
		}
	}

	counter = 0;
	i = 0;
	while (i < n && smallestInd != -1 && counter < n-smallestInd) {
		if (a[smallestInd+i] > separator) {
			rotateLeft(a, n, smallestInd+i);
			counter++;
		} else {
			i++;
			counter++;
		}
	}

	if (smallestInd != -1) {
		return smallestInd;
	}

	return n;
}

//DELETE
void printArr(string a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
}