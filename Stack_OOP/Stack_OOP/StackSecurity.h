#pragma once
class StackSecurity
{
	StackSecurity();
	static bool canaryTest(char canary);
private:
	static char canarySample;
};

StackSecurity::StackSecurity() {
	srand(std::time(0));
	canarySample = rand() % sizeof(char);
}

bool StackSecurity::canaryTest(char canary) {
	return canary == canarySample;
}

