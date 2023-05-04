
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <type_traits>
#include "include/BinaryRelation.h"
#include "include/Color.h"
#include "include/InOrderIntRelation.h"
#include "include/ReverseOrderIntRelation.h"
#include "include/ColorBrightnessRelation.h"
#include "include/ColorValuesRelation.h"

using namespace std;
static InOrderIntRelation singletonIntRelation;

#pragma region array_utility
string to_string(Color& c) {
	return "(" + std::to_string(c.getRed()) + ", " + to_string(c.getGreen()) + ", " + to_string(c.getBlue()) + ")";
}

template <class T>
void printArray(T* a, int size) {
	cout << "------------------------------------------------------" << endl;
	cout << "[";
	for (int i = 0; i < size; i++) {
		cout << to_string(a[i]);
		if (i < size - 1) cout << ", ";
	}
	cout << "]" << endl << endl;
}
#pragma endregion

#pragma region insertionSort_original
void insertionSort(unsigned int* a, int size) {
	for (int i = 1; i < size; i++) {
		int j = i;
		while (j > 0 && a[j - 1] > a[j]) {
			swap(a[j], a[j-1]);
			j--;
		}
	}
}
#pragma endregion

#pragma region insertionSort_template
template <class T>
void templateInsertionSort(T* a, int size, BinaryRelation<T, T> &relationReference) {
	std::cout << "Using insertion sort\n";
	for (int i = 1; i < size; i++) {
		int j = i;
		//a[j - 1] > a[j] -> inRelation(a[j], a[j-1])
		//not: inRelation returns true if left <= right, so either !inRelation or flip parameters
		while (j > 0 && relationReference.inRelation(a[j], a[j-1])) {
			swap(a[j], a[j-1]);
			j--;
		}
	}
}
#pragma endregion

#pragma region quicksort_original
void quickSort(unsigned int* a, int left, int right) {
	int i = left;
	int j = right;
	while (j > i) {
		if (a[i] < a[i+1]) {
			swap(a[i + 1], a[j]);
			j--;
		} else {
			swap(a[i], a[i + 1]);
			i++;
		}
	}
	if (left < i - 1) quickSort(a, left, i - 1);
	if (right > i + 1) quickSort(a, i + 1, right);
}

void quickSort(unsigned int* a, int size) {
	quickSort(a, 0, size - 1);
}
#pragma endregion

#pragma region quicksort_template
template<class T>
void templateQuickSort(T* a, int left, int right, BinaryRelation<T, T> &relationReference) {
	int i = left;
	int j = right;
	while (j > i) {
		//a[i] < a[i+1]	-> 		inRelation(a[i], a[i+1])
		//note: inRelation returns true if left <= right
		if (relationReference.inRelation(a[i], a[i+1])) {
			swap(a[i + 1], a[j]);
			j--;
		} else {
			swap(a[i], a[i + 1]);
			i++;
		}
	}
	if (left < i - 1) templateQuickSort(a, left, i - 1, relationReference);
	if (right > i + 1) templateQuickSort(a, i + 1, right, relationReference);
}

template<class T>
void templateQuickSort(T* a, int size, BinaryRelation<T, T> &relationReference) {
	std::cout << "Using quick sort\n";
	templateQuickSort(a, 0, size - 1, relationReference);
}
#pragma endregion

#pragma region countingSort_original
void countingSort(unsigned int* a, int size) {
	std::cout << "Using counting sort\n";
	unsigned int max = 0;
	for (int i = 0; i < size; i++) {
		if (a[i] > max) max = a[i];
	}
	int* b = new int[max + 1];
	for (unsigned int i = 0; i <= max; i++) {
		b[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		b[a[i]]++;
	}
	int j = 0;
	for (unsigned int i = 0; i <= max; i++) {
		for (int k = 0; k < b[i]; k++) {
			a[j] = i;
			j++;
		}
	}
	delete[] b;
}
#pragma endregion

#pragma region randomArray
Color* getRandomColorArrayOfSize(int size) {
	Color* a = new Color[size];
	for (int i = 0; i < size; i++) {
		int r = rand() & 0xff;
		int g = rand() & 0xff;
		int b = rand() & 0xff;
		a[i] = Color(r, g, b);
	}
	return a;
}

unsigned int* getRandomIntArrayOfSize(int size) {
	unsigned int* a = new unsigned int[size];
	for (int i = 0; i < size; i++) {
		a[i] = rand() & 0b1111;
	}
	return a;
}
#pragma endregion

#pragma region wildcardSort
template<class T>
void sort(T* a, int size, BinaryRelation<T, T> &relationReference = singletonIntRelation)
{
	if(size <= 16)
		templateInsertionSort(a, size, relationReference);
	else
	 	templateQuickSort(a, size, relationReference);
}

void sort(unsigned int* a, int size, BinaryRelation<unsigned int, unsigned int> &relationReference = singletonIntRelation)
{
	countingSort(a, size);
}
#pragma endregion

int main() {
	srand(static_cast<unsigned int>(time(nullptr)));
    
    // START YOUR TESTS HERE!
	InOrderIntRelation inOrderIntegerComparer;
	ReverseOrderIntRelation reverseOrderIntegerComparer;
	ColorBrightnessRelation brightnessColorComparer;
	ColorValuesRelation valuesColorComparer;
	
	#pragma region testInsertionSortInt
	unsigned int* integerArray = getRandomIntArrayOfSize(100);
	cout << "Randomly assigned array:\n";
	printArray(integerArray, 100);

	templateInsertionSort(integerArray, 100, inOrderIntegerComparer);

	cout << "Sorted array using insertionSort:\n";
	printArray(integerArray, 100);
	#pragma endregion

	#pragma region testQuickSortInt
	integerArray = getRandomIntArrayOfSize(100);
	cout << "Randomly assigned array:\n";
	printArray(integerArray, 100);

	templateQuickSort(integerArray, 100, inOrderIntegerComparer);

	cout << "Sorted array using quickSort:\n";
	printArray(integerArray, 100);
	#pragma endregion

	#pragma region testInsertionSortColor
	Color* colorArray = getRandomColorArrayOfSize(100);
	cout << "Randomly assigned array:\n";
	printArray(colorArray, 100);

	templateInsertionSort(colorArray, 100, brightnessColorComparer);

	cout << "Sorted array using insertionSort:\n";
	printArray(colorArray, 100);
	#pragma endregion

	#pragma region testQuickSortColor
	colorArray = getRandomColorArrayOfSize(100);
	cout << "Randomly assigned array:\n";
	printArray(colorArray, 100);

	templateQuickSort(colorArray, 100, brightnessColorComparer);

	cout << "Sorted array using quickSort:\n";
	printArray(colorArray, 100);
	#pragma endregion

	#pragma region testWildcardSort
	integerArray = getRandomIntArrayOfSize(100);
	cout << "Randomly assigned array:\n";
	printArray(integerArray, 100);

	sort(integerArray, 100);

	cout << "Sorted array using counting sort based on type:\n";
	printArray(integerArray, 100);

	colorArray = getRandomColorArrayOfSize(10);
	cout << "Randomly assigned array:\n";
	printArray(colorArray, 10);

	sort(colorArray, 10, brightnessColorComparer);

	cout << "Sorted array using insertion/quick/counting sort based on size and type:\n";
	printArray(colorArray, 10);

	colorArray = getRandomColorArrayOfSize(20);
	cout << "Randomly assigned array:\n";
	printArray(colorArray, 20);

	sort(colorArray, 20, brightnessColorComparer);

	cout << "Sorted array using insertion/quick/counting sort based on size and type:\n";
	printArray(colorArray, 20);
	#pragma endregion

	delete integerArray;
	delete colorArray;
	return 0;
}