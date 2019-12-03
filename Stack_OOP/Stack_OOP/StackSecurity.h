#pragma once
class StackSecurity
{
public:
	static void Init();
	static bool canaryTest(char canary);
	static char GetCanarySample();
private:
	static char canarySample;
};

char StackSecurity::canarySample;

void StackSecurity::Init() {
	if (canarySample == 0) {
		srand((unsigned int)std::time(0));
		canarySample = (char)rand() % 255 + 1;
	}
}
//Returns true if canary is OK
bool StackSecurity::canaryTest(char canary) {
	return canary == canarySample;
}
//Returns canary sample
char StackSecurity::GetCanarySample() {
	return canarySample;
}

