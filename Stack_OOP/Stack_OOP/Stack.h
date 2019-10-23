#pragma once
#include <stdlib.h>
#include <assert.h>
#include "Print.h"
#define S_SUCCESS 0
#define S_EMPTY_STACK 1
#define S_OUT_OF_MEMORY 2
template <typename T>
class Stack
{
public:
	Stack(int cap) {
		data = (T*)calloc(cap, sizeof(T));
		capacity = cap;
		size = 0;
	}
	~Stack() {
		free(data);
	}

	void Push(T value) {
		if (size >= capacity) {
			capacity = size + 1;
			data = (T*)realloc(data, capacity * sizeof(T));
			if (data == nullptr) OK(S_OUT_OF_MEMORY);
		}
		data[size] = value;
		size++;
	}

	T Pop() {
		if (size == 0) OK(S_EMPTY_STACK);
		size--;
		return data[size];
	}

	T Top() {
		if (size == 0) OK(S_EMPTY_STACK);
		return data[size - 1];
	}

	bool IsEmpty() {
		return size == 0 ? true : false;
	}

	size_t GetSize() {
		return size;
	}

	size_t GetCapacity() {
		return capacity;
	}

private:
	T* data;
	size_t capacity, size;

	void OK(int code) {
		switch (code)
		{
		case S_SUCCESS:
			break;
		case S_EMPTY_STACK:
			Print("Error, empty stack");
			assert(("Error, empty stack", 0));
			break;
		case S_OUT_OF_MEMORY:
			Print("Error, out of memory");
			assert(("Error, out of memory", 0));
			break;
		default:
			Print("Unknown error");
			assert(("Unknown error", 0));
		}
	}
};