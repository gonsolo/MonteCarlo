#include <cstdlib>
#include <cmath>
#include <iostream>
#include <random>

using namespace std;
const char newline = '\n';

auto f = [](float x) { return powf(x, 3); };
auto antiderivative = [](float x) { return pow(x, 4) / 4; };

float analytical(float a, float b) {
	return antiderivative(b) - antiderivative(a);
}

float montecarlo(float a, float b) {

	default_random_engine generator;
	uniform_real_distribution<float> distribution(a, b);
	auto rand = [&distribution, &generator]() { return distribution(generator); };

	int resolution = 1000;
	float result = 0;
	for (int i = 0; i < resolution; ++i) {
		auto x = rand();
		auto y = f(x);
		result += y;
	}
	result /= resolution;

	return result;
}

int main()
{
	float a = 0;
	float b = 1;

	cout << "Analytical solution of x^3 from 0 to 1: " << analytical(a, b) << newline;
	cout << "Monte Carlo solution: " << montecarlo(a, b) << newline;

	return  EXIT_SUCCESS;
}

