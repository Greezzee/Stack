#pragma once
#include <stdio.h>
void Print(int val) {
	printf("%d", val);
}
void Print(unsigned int val) {
	printf("%ud", val);
}
void Print(long val) {
	printf("%ld", val);
}
void Print(unsigned long val) {
	printf("%uld", val);
}
void Print(long long val) {
	printf("%lld", val);
}
void Print(unsigned long long val) {
	printf("%ulld", val);
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