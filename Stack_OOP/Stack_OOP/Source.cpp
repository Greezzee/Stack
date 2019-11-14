#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <ctime>
//#include "StackSecurity.h"
#include "Stack.h"
#include "Print.h"
int main() {
	Stack<int> stk_i(0);
	stk_i.Push(12);
	stk_i.Push(43);
	Stack<char*> stk_s;
	stk_s.Push((char*)"Hello");
	stk_s.Push((char*)"World");
	stk_s.Push((char*)"Square");
	stk_s.Push((char*)"Bla bla bla");
	stk_i.Pop();
	stk_i.Pop();
	stk_i.Top();
	stk_i.PrintDump(stdout);
	stk_s.PrintDump(stdout);
	return 0;
}