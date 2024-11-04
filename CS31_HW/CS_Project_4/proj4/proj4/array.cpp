#include <iostream>
#include <string>
#include <cassert>
using namespace std;

/*
Make Sure to Add the "Notwithstanding" checks (return -1)
DO NOT COMPARE TWO STRING LITERALS  "help" < "hello" (FAQ)
DELETE COUT AND "DELETE" comments
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
	return 0;
}


int appendToAll(string a[], int n, string value) {
	if (n < 0) {
		return -1;
	}
	for (int i = 0; i < n; i++) {
		a[i] += value;
	}
	return n;
}

int lookup(const string a[], int n, string target) {
	if (n < 0) {
		return -1;
	}
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
	int maxCounter = 0;
	for (int i = 0; i < n; i++) {
		string currentString = a[i];
		for (int j = 0; j < n; j++) {
			if (!(currentString >= a[j])) {
				maxCounter = 0;
				break;
			}
			maxCounter++;
		}
		if (maxCounter == n) {
			return i;
		}
	}
	return -1;
}

int rotateLeft(string a[], int n, int pos) {
	if (n < 0 || pos >= n) {
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
	if (n1 < 0 || n2 < 0) {
		return -1;
	}

	int trackSeq = 0;
	int subSeqIter = 0;
	for (int i = 0; i < n1; i++) {
		if (trackSeq == n2) {
			return (i - n2);
		}

		if (a1[i] == a2[subSeqIter]) {
			trackSeq++;
			subSeqIter++;
		} else {
			trackSeq = 0;
			subSeqIter = 0;
		}
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
	//Deal with (all a[i] == separator)
	int smallestInd = -1; //FIXME: CHECK THIS TEST CASES
	for (i = 0; i < n; i++) {
		if (a[i] >= separator) {
			smallestInd = i;
			break;
		}
	}

	cout << "Before: ";
	printArr(a, n);

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
	cout << "After: ";
	printArr(a, n);

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