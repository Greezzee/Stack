#pragma once
#include <stdio.h>
void Print(int val) {
	printf("%d", val);
}
void Print(unsigned int val) {
	printf("%u", val);
}
void Print(long val) {
	printf("%ld", val);
}
void Print(unsigned long val) {
	printf("%lu", val);
}
void Print(long long val) {
	printf("%lld", val);
}
void Print(unsigned long long val) {
	printf("%llu", val);
}
void Print(float val) {
	printf("%g", val);
}
void Print(double val) {
	printf("%lg", val);
}
void Print(long double val) {
	printf("%Lg", val);
}
void Print(char val) {
	printf("%c", val);
}
void Print(char* val) {
	printf("%s", val);
}
void Print(const char val[]) {
	printf("%s", val);
}

void Println(int val) {
	printf("%d\n", val);
}
void Println(unsigned int val) {
	printf("%u\n", val);
}
void Println(long val) {
	printf("%ld\n", val);
}
void Println(unsigned long val) {
	printf("%lu\n", val);
}
void Println(long long val) {
	printf("%lld\n", val);
}
void Println(unsigned long long val) {
	printf("%llu\n", val);
}
void Println(float val) {
	printf("%g\n", val);
}
void Println(double val) {
	printf("%lg\n", val);
}
void Println(long double val) {
	printf("%Lg\n", val);
}
void Println(char val) {
	printf("%c\n", val);
}
void Println(char* val) {
	printf("%s\n", val);
}
void Println(const char val[]) {
	printf("%s\n", val);
}