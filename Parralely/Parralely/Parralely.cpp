#include "pch.h"
#include <omp.h>
#include <iostream>
#include <vector>
#include <ctime>
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
	// массив б имеет операционную зависимость. нужно ее обойти проанализировав задание 
	DWORD t1;
	int i = 1, k, left, right;
	double x, sum = 0;
	bool output;
	while (true) {
		std::cin >> N >> x >> k >> output;
		int round = N / k;
		//std::cout << round << std::endl;	
		std::vector<double> a(N);
		std::vector<double> b(N);
		std::vector<double> c(N);
		//																	START TIME

	//parallel_solution
		t1 = GetTickCount();
		a[0] = x * N;
		b[0] = x * x;
#pragma omp parallel private(i, sum, left, right) num_threads(k)
		{
			i = omp_get_thread_num();
			left = round * i;
			right = ((k - 1) != i) ? round * (i + 1) : N;
			for (int j = left; j < right; j++)
			{
				if (j != 0)
				{
					sum = 0;
					a[j] = exp(double(x * j)) + double(x * j);
					for (int t = 0; t < j + 1; t++)
					{
						sum += double(t) * pow(x, double(t - 1));
					}
					b[j] = ((x * x) + sum) / pow(x, double(j));
				}
			}
		}
		/*func(a);
		func(b);*/
#pragma omp parallel private(i, left, right) num_threads(k)
		{
			i = omp_get_thread_num();
			left = round * i;
			right = ((k - 1) != i) ? round * (i + 1) : N;
			for (int j = left; j < right; j++)
			{
				c[j] = (a[j] * b[N - (j + 1)]) / double(j + 1);
			}
		}
		//func(c);
#pragma omp parallel private(i, left, right) num_threads(k)
		{
			i = omp_get_thread_num();
			left = round * i;
			right = ((k - 1) != i) ? round * (i + 1) : N;
			for (int j = left; j < right; j++)
			{
				b[j] = (a[j] + c[j]) / 2;
			}
		}


		//parallel_solution
		std::cout << "search_time for parallel_solution: " << GetTickCount() - t1 << std::endl;//				OVER TIME
		if (output) 
		{
			func(a);
			func(b);
			func(c);
		}
	}
}