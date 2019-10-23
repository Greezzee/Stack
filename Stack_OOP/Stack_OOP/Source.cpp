#include "Stack.h"
#include "Print.h"

int main() {
	Stack<int> stk_i(0);
	stk_i.Push(12);
	stk_i.Push(43);
	Println(stk_i.Pop());
	Println(stk_i.Pop());
	Println (stk_i.GetSize());
	return 0;
}