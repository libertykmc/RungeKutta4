#include <iostream>
#include <math.h>
#include <Windows.h>
#include <omp.h>

const int n = 2;
const int m = 4;
const double t0 = 0.0;
const double tmax = 10.0;
double t = t0;
const double tau = 0.001;
double y[n] = { 0.0, 0.125 };
double yy[n] = { 0.0,0.0 };
double ff[n] = { 0.0, 0.0 };
double R[n][m] = {0.0};

double f(double* y, double x, int i)
{
	double w;

	switch (i)
	{
	case 0: w = y[1];
		break;

	case 1: w = -0.07 * x * y[1] - x * x * y[0];
		break;
	}

	return w;
}

int main()
{
	double time_begin, time_end, time_elapsed;

	time_begin = omp_get_wtime();

	for (double t = t0; t <= tmax; t += tau)
	{
		for (int i = 0; i < n; i++)
		{
			R[i][0] = tau * f(y, t, i);
			yy[i] = y[i] + 0.5 * R[i][0];
		}

		for (int i = 0; i < n; i++)
		{
			R[i][1] = tau * f(yy, t + tau*0.5, i);
		}

		for (int i = 0; i < n; i++)
		{
			yy[i] = y[i] + R[i][1] * 0.5;
		}

		for (int i = 0; i < n; i++)
		{
			R[i][2] = tau * f(yy, t + tau * 0.5, i);
		}

		for (int i = 0; i < n; i++)
		{
			yy[i] = y[i] + R[i][2];
		}

		for (int i = 0; i < n; i++)
		{
			R[i][3] = tau * f(yy, t + tau, i);
		}

		for (int i = 0; i < n; i++)
		{
			y[i] += (R[i][0] + 2.0 * R[i][1] + 2.0 * R[i][2] + R[i][3]) / 6.0;
		}
	}

	time_end = omp_get_wtime();

	time_elapsed = time_end - time_begin;

	std::cout << "time = " << time_elapsed << std::endl;

	for (int i = 0; i < n; i++)
	{
		std::cout << "y[" << i << "] " << y[i] << std::endl;
	}

	system("pause");

}
//Рунге-Кутты 4