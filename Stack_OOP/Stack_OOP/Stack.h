#pragma once
#include <stdlib.h>
#include <assert.h>
#include "Print.h"

enum ErrorCodes {
	SUCCESS,
	ERR_EMPTY_STACK,
	ERR_OUT_OF_MEMORY,
	ERR_CANARY_BREAKE
};

template <typename T>
class Stack
{
public:
	Stack();

	//Construct with start capacity
	Stack(int cap);

	~Stack();

	//Push element to the end of stack. Resize it if capacity less size
	void Push(T value);

	//Returns element from top and deletes it from data
	T Pop();

	//Returns element from top
	T Top();

	//Return true if stack empty. Else return false.
	bool IsEmpty();

	size_t GetSize();
	size_t GetCapacity();

	//Print information about stack to file or stdout
	void PrintDump(FILE* file);
private:
	char enterCanary;
	StackSecurity securityModule;
	T* data;
	size_t capacity, size;
	char exitCanary;

	//Change size of data array
	void Resize(size_t newSize);
	//Test for error codes
	void OK(ErrorCodes code, const char* funcName);
	//Print element data[index] in format: index - pointer - element
	void PrintElement(FILE* file, int index);
	//returns true if all canarys are OK. Else returns false
	bool CanaryCheck() {
		return securityModule.canaryTest(enterCanary) && securityModule.canaryTest(exitCanary);
	}
};


template <typename T>
Stack<T>::Stack(int cap) {
	data = (T*)calloc(cap, sizeof(T));
	capacity = cap;
	size = 0;
	enterCanary = securityModule.GetCanarySample();
	exitCanary = securityModule.GetCanarySample();
}

template <typename T>
Stack<T>::Stack() {
	data = nullptr;
	capacity = 0;
	size = 0;
	enterCanary = securityModule.GetCanarySample();
	exitCanary = securityModule.GetCanarySample();
}

template <typename T>
Stack<T>::~Stack() {
	if (!CanaryCheck())
		OK(ERR_CANARY_BREAKE, "destructor");
	free(data);
}

template <typename T>
void Stack<T>::Push(T value) {
	if (!CanaryCheck())
		OK(ERR_CANARY_BREAKE, "Push()");
	if (size >= capacity) {
		Resize(size + 1);
		if (data == nullptr) OK(ERR_OUT_OF_MEMORY, "Push()");
	}
	data[size] = value;
	size++;
}

template <typename T>
T Stack<T>::Pop() {
	if (!CanaryCheck())
		OK(ERR_CANARY_BREAKE, "Pop()");
	if (size == 0) OK(ERR_EMPTY_STACK, "Pop()");
	size--;
	return data[size];
}

template <typename T>
T Stack<T>::Top() {
	if (!CanaryCheck())
		OK(ERR_CANARY_BREAKE, "Top()");
	if (size == 0) OK(ERR_EMPTY_STACK, "Top()");
	return data[size - 1];
}

template <typename T>
bool Stack<T>::IsEmpty() {
	if (!CanaryCheck())
		OK(ERR_CANARY_BREAKE, "IsEmpty()");
	return size == 0 ? true : false;
}

template <typename T>
void Stack<T>::Resize(size_t newSize) {
	capacity = newSize;
	if (size >= capacity) size = capacity;
	T* newData = (T*)realloc(data, capacity * sizeof(T));
	data = newData;
}

template <typename T>
void Stack<T>::OK(ErrorCodes code, const char* funcName) {
	FILE* logs = fopen("logs.txt", "w");
	PrintDump(stdout);
	PrintDump(logs);
	fclose(logs);
	switch (code)
	{
	case SUCCESS:
		break;
	case ERR_EMPTY_STACK:
		printf("Error, empty stack at %s function\n", funcName);
		assert(0);
		break;
	case ERR_OUT_OF_MEMORY:
		printf("Error, out of memory at %s function\n", funcName);
		assert(0);
		break;
	case ERR_CANARY_BREAKE:
		printf("Error, broke canary detected at %s call\n", funcName);
		assert(0);
		break;
	default:
		printf("Unknown error\n");
		assert(0);
		break;
	}
}

template <typename T>
size_t Stack<T>::GetSize() {
	return size;
}

template <typename T>
size_t Stack<T>::GetCapacity() {
	return capacity;
}




/*
	Dump functions:
*/

template <typename T>
void Stack<T>::PrintDump(FILE* file) {
	if (!CanaryCheck())
		OK(ERR_CANARY_BREAKE, "PrintDump()");
	fprintf(file, "------------------------------------------------\n");
	fprintf(file, "Stack's dump at [0x%p]\n", this);
	fprintf(file, "Size:     %d\nCapacity: %d\n", size, capacity);
	fprintf(file, "Data's memory sector: [0x%p] - [0x%p]\n", data, data + capacity - 1);
	fprintf(file, "[i] -   Pointer   - Data:\n");
	for (unsigned int i = 0; i < size; i++) {
		PrintElement(file, i);
	}
	for (int i = size; i < capacity; i++) {
		fprintf(file, "[%d]: [0x%p] - [Empty]\n", i, data + i);
	}
	fprintf(file, "------------------------------------------------\n");
}

template <typename T>
void Stack<T>::PrintElement(FILE* file, int index) {
	fprintf(file, "[%d]: [0x%p] - [0x%p]\n", index, data + index, data[index]);
}

template <>
void Stack<int>::PrintElement(FILE* file, int index) {
	fprintf(file, "[%d]: [0x%p] - [%d]\n", index, data + index, data[index]);
}

template <>
void Stack<long>::PrintElement(FILE* file, int index) {
	fprintf(file, "[%d]: [0x%p] - [%ld]\n", index, data + index, data[index]);
}

template <>
void Stack<long long>::PrintElement(FILE* file, int index) {
	fprintf(file, "[%d]: [0x%p] - [%lld]\n", index, data + index, data[index]);
}

template <>
void Stack<float>::PrintElement(FILE* file, int index) {
	fprintf(file, "[%d]: [0x%p] - [%g]\n", index, data + index, data[index]);
}

template <>
void Stack<double>::PrintElement(FILE* file, int index) {
	fprintf(file, "[%d]: [0x%p] - [%lg]\n", index, data + index, data[index]);
}

template <>
void Stack<long double>::PrintElement(FILE* file, int index) {
	fprintf(file, "[%d]: [0x%p] - [%Lg]\n", index, data + index, data[index]);
}

template <>
void Stack<char>::PrintElement(FILE* file, int index) {
	fprintf(file, "[%d]: [0x%p] - ['%c']\n", index, data + index, data[index]);
}

template <>
void Stack<char*>::PrintElement(FILE* file, int index) {
	fprintf(file, "[%d]: [0x%p] - [\"%s\"]\n", index, data + index, data[index]);
}