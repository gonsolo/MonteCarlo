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

float metropolis(float a, float b) {

	default_random_engine generator;
	uniform_real_distribution<float> distribution(a, b);
	auto rand = [&distribution, &generator]() { return distribution(generator); };
	typedef struct {
		float x;
		float y;
	} XY;

	uniform_real_distribution<float> distribution2(-0.1f, 0.1f);
	auto m = [&distribution2, &generator]() { return distribution2(generator); };

	auto mutate = [&m, &a, &b](XY input) {
		XY result;
		auto x = input.x + m();
		if (x >= a && x <= b)
			result.x = x;
		else
			result.x = input.x;
		result.y = f(result.x);
		return result;
	};

	int resolution = 1000;
	XY start;
	start.x = rand();
	start.y = f(start.x);
	float result = 0;

	for (int i = 0; i < resolution; ++i) {

		auto m = mutate(start);

		result += m.y;
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
	cout << "(Wrong) Metropolis solution: " << metropolis(a, b) << newline;

	return  EXIT_SUCCESS;
}

