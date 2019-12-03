#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <ctime>
#include "StackSecurity.h"
#include "Stack.h"
#include "Print.h"

struct test {
	int x, y;
};

int main() {
	Stack<test> stk_i(1);
	int a = 12, b = 43;
	stk_i.Push({1, 2});
	stk_i.Push({100, 200});
	Stack<char*> stk_s;
	stk_s.Push((char*)"Hello");
	stk_s.Push((char*)"World");
	stk_s.Push((char*)"Square");
	stk_s.Push((char*)"Bla bla bla");
	stk_i.PrintDump(stdout);
	stk_s.PrintDump(stdout);
	return 0;
}