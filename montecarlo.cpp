#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;
const char newline = '\n';

auto f = [](float x) { return pow(x, 3); };
auto antiderivative = [](float x) { return pow(x, 4) / 4; };

float analytical(float a, float b) {
	return antiderivative(b) - antiderivative(a);
}

int main()
{
	float a = 0;
	float b = 1;

	cout << "Analytical solution of x^3 from 0 to 1: " << analytical(a, b) << newline;

	return  EXIT_SUCCESS;
}

