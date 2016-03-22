#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <sstream>

using namespace std;

int main(int argc, char** argv) {
		
	int alg = 1;
	int n_omp = 0;
	int size_min = 600;
	int size_max = 3000;
	int size_inc = 400;
	
	if (argc > 1) alg = 	atoi(argv[1]);
		if (alg > 1) return 1;
	if (argc > 2) n_omp = 	atoi(argv[2]);
		if (alg > 8) return 1;
	if (argc > 3) size_min = atoi(argv[3]);
	if (argc > 4) size_max = atoi(argv[4]);
	if (argc > 5) size_inc = atoi(argv[5]);
		
	
	for(int i = 0; i <= n_omp; i++) {
	for(int size = size_min; size <= size_max; size += size_inc) {
		
		cout << alg << " " << size << " " << i << endl;

	}}
	
	return 0;
}
