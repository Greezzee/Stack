#include "Stack.h"
#include "Print.h"

int main() {
	Stack<int> stk_i(0);
	stk_i.Push(12);
	stk_i.Push(43);
	Print(stk_i.Top());
	Print("\n");
	Print(stk_i.Pop());
	Print("\n");
	Print(stk_i.Top());
	Print("\n");
	return 0;
}