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
//Returns true if canary is OK
bool StackSecurity::canaryTest(char canary) {
	return canary == canarySample;
}
//Returns canary sample
char StackSecurity::GetCanarySample() {
	return canarySample;
}

