#pragma once
class StackSecurity
{
public:
	StackSecurity();
	bool canaryTest(char canary);
	char GetCanarySample();
private:
	char canarySample;
};

StackSecurity::StackSecurity() {
	srand((unsigned int)std::time(0));
	canarySample = (char)rand();
}
bool StackSecurity::canaryTest(char canary) {
	return canary == canarySample;
}
char StackSecurity::GetCanarySample() {
	return canarySample;
}

