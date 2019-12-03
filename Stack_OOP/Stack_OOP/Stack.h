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

	long long GetHash();

private:
	char enterCanary;
	T* data;
	size_t capacity, size;
	long long hash;
	char exitCanary;

	long long CalculateHash();


	//Change size of data array
	void Resize(size_t newSize);
	//Test for error codes
	void OK(ErrorCodes code, const char* funcName);
	//Print element in format [elem]
	void PrintElement(FILE* file, T* elem);
	//returns true if all canarys are OK. Else returns false
	bool CanaryCheck() {
		return StackSecurity::canaryTest(enterCanary) && StackSecurity::canaryTest(exitCanary);
	}
};


template <typename T>
Stack<T>::Stack(int cap) {
	data = (T*)calloc(cap, sizeof(T));
	capacity = cap;
	size = 0;
	hash = 0;
	StackSecurity::Init();
	enterCanary = StackSecurity::GetCanarySample();
	exitCanary = StackSecurity::GetCanarySample();
}

template <typename T>
Stack<T>::Stack() {
	data = nullptr;
	capacity = 0;
	size = 0;
	hash = 0;
	StackSecurity::Init();
	enterCanary = StackSecurity::GetCanarySample();
	exitCanary = StackSecurity::GetCanarySample();
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
		Resize((size + (size == 0)) * 2);
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

template <typename T>
long long Stack<T>::CalculateHash()
{
	hash = 1;
	char* dataToHash = (char*)data;
	for (size_t i = 0; i < capacity * sizeof(T); i++) {
		hash *= (long long)abs(dataToHash[i]) + i;
		hash = hash % 286331153;
	}
	return hash;
}

template <typename T>
long long Stack<T>::GetHash() {
	if (hash == 0)
		CalculateHash();
	return hash;
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
	fprintf(file, "Stack's hash: %lld\n", GetHash());
	fprintf(file, "Data's memory sector: [0x%p] - [0x%p]\n", data, data + capacity - 1);
	fprintf(file, "[i] -   Pointer   - Data:\n");
	for (unsigned int i = 0; i < size; i++) {
		fprintf(file, "[%d]: [0x%p] - ", i, data + i);
		PrintElement(file, &data[i]);
		fprintf(file, "\n");
	}
	for (int i = size; i < capacity; i++) {
		fprintf(file, "[%d]: [0x%p] - [Empty]\n", i, data + i);
	}
	fprintf(file, "------------------------------------------------\n");
}

template <typename T>
void Stack<T>::PrintElement(FILE* file, T* elem) {
	fprintf(file, "[0x%p]", *elem);
}

template <>
void Stack<int>::PrintElement(FILE* file, int* elem) {
	fprintf(file, "[%d]", *elem);
}

template <>
void Stack<long>::PrintElement(FILE* file, long* elem) {
	fprintf(file, "[%ld]", *elem);
}

template <>
void Stack<long long>::PrintElement(FILE* file, long long* elem) {
	fprintf(file, "[%Ld]", *elem);
}

template <>
void Stack<float>::PrintElement(FILE* file, float* elem) {
	fprintf(file, "[%g]", *elem);
}

template <>
void Stack<double>::PrintElement(FILE* file, double* elem) {
	fprintf(file, "[%lg]", *elem);
}

template <>
void Stack<long double>::PrintElement(FILE* file, long double* elem) {
	fprintf(file, "[%Lg]", *elem);
}

template <>
void Stack<char>::PrintElement(FILE* file, char* elem) {
	fprintf(file, "[%c]", *elem);
}

template <>
void Stack<char*>::PrintElement(FILE* file, char** elem) {
	fprintf(file, "[%s]", *elem);
}