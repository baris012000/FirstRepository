#include "pch.h"
#include <iostream>
#include <vector>
#include <Windows.h>
typedef unsigned long DWORD;
//419
int N;
void func(std::vector<double> a)
{
	int N = a.size();
	for (int i = 0; i < N; i++) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	DWORD t2;
	int i = 1, k;
	double x, sum = 0;
	bool output;
	while (true) {
		std::cin >> N >> x >> output;
		std::vector<double> a(N);
		std::vector<double> b(N);
		std::vector<double> c(N);
		t2 = GetTickCount();
		a[0] = x * N;
		b[0] = x * x;
		for (int i = 1; i < N; i++) {
			a[i] = double(exp(double(x * i)) + x * i);
			b[i] = (double(b[i - 1] + i)) / x;
		}
		for (int i = 0; i < N; i++) {
			c[i] = a[i] * b[(N - 1) - i] / (i + 1);
		}
		for (int i = 0; i < N; i++) {
			b[i] = (a[i] + c[i]) / 2;
		}
		std::cout << "search_time for consistently_solution: " << GetTickCount() - t2 << std::endl;
		if (output)
		{
			func(a);
			func(b);
			func(c);
		}
	}
}