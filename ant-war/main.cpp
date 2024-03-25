#include <iostream>
#include <random>
#include <vector>
#include <cmath>

#include "Simulator.hpp"

float const PI = 3.1415927f;


int main(int argc, char** argv)
{
	int N = 10;
	Simulator Simu(N);
	int a;
	
	Simu.init();
	a = Simu.Simulation();

	return 0;
}

