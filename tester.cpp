#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <sstream>

using namespace std;

int main(int argc, char** argv) {
		
	for(int line_mult = 0; line_mult<=1; line_mult++)
	for(int size = 600; size < 3000; size += 400) {
		
		cout << line_mult << " " << size << endl;
		
	}
	
	return 0;
}