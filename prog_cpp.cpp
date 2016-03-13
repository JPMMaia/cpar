//#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <papi.h>

using namespace std;

#define SYSTEMTIME clock_t
 
double OnMult(int size, bool line_mult, unsigned n_omp) 
{
	
	SYSTEMTIME Time1, Time2;
	
	char st[100];
	double temp;
	int i, j, k;

	double *a, *b, *c;
	

		
    a = (double *)malloc((size * size) * sizeof(double));
	b = (double *)malloc((size * size) * sizeof(double));
	c = (double *)malloc((size * size) * sizeof(double));

	for(i=0; i<size; i++)
		for(j=0; j<size; j++)
			a[i*size + j] = (double)1.0;



	for(i=0; i<size; i++)
		for(j=0; j<size; j++)
			b[i*size + j] = (double)(i+1);



    Time1 = clock();

	if(n_omp == 0) {
		// Normal Calculation
		if (!line_mult) {
			// Normal Order
			for(i=0; i<size; i++) {	
				for( j=0; j<size; j++) {	
					for( k=0; k<size; k++) {	
						c[i*size+j] += a[i*size+k] * b[k*size+j];
					}
				}
			}
		} else {
			// Line Mult Order
			for(i=0; i<size; i++) {	
				for( k=0; k<size; k++) {	
					for( j=0; j<size; j++) {	
						c[i*size+j] += a[i*size+k] * b[k*size+j];
					}
				}
			}
		}
	}
	else {
		// OMP Calculation
		if (!line_mult) {
			// Normal Order
			#pragma omp parallel for num_threads(n_omp)
			for(i=0; i<size; i++) {	
				for( j=0; j<size; j++) {	
					for( k=0; k<size; k++) {	
						c[i*size+j] += a[i*size+k] * b[k*size+j];
					}
				}
			}
		} else {
			// Line Mult Order
			#pragma omp parallel for num_threads(n_omp)
			for(i=0; i<size; i++) {	
				for( k=0; k<size; k++) {	
					for( j=0; j<size; j++) {	
						c[i*size+j] += a[i*size+k] * b[k*size+j];
					}
				}
			}
		}
	}

    Time2 = clock();


	/*
	cout << "Result matrix: " << endl;
	for(i=0; i<1; i++)
	{	for(j=0; j<min(10,m_br); j++)
			cout << phc[j] << " ";
	}
	cout << endl;
	*/

    free(a);
    free(b);
    free(c);
	
	return (double)(Time2 - Time1) / CLOCKS_PER_SEC;
	
}



void handle_error (int retval)
{
  printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
  exit(1);
}

void init_papi() {
  int retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT && retval < 0) {
    printf("PAPI library version mismatch!\n");
    exit(1);
  }
  if (retval < 0) handle_error(retval);

  std::cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
            << " MINOR: " << PAPI_VERSION_MINOR(retval)
            << " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}

int main (int argc, char *argv[])
{
	
	// PAPI vars
	int EventSet = PAPI_NULL;
  	long long values[2];
  	int ret;
	
	
	// Setup PAPI
	ret = PAPI_library_init( PAPI_VER_CURRENT );
	if ( ret != PAPI_VER_CURRENT )
		std::cout << "FAIL" << endl;


	ret = PAPI_create_eventset(&EventSet);
		if (ret != PAPI_OK) cout << "ERRO: create eventset" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L1_DCM);
	if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_DCM" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L2_DCM);
	if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_DCM" << endl;

	cout << "algorithm ";
	cout << "mat_size ";
	cout << "time(s) ";
	cout << "PAPI_L1_TCM ";
	cout << "PAPI_L2_TCM " << endl;
	
	// Do work

	bool line_mult;
	int mat_size;
	int n_omp;
	do {
		// Input
		if (argc >= 4) {
			line_mult = (atoi(argv[1]) == 1);
			mat_size = atoi(argv[2]);
			n_omp = atoi(argv[3]);
		} else {
			if (!(cin >> line_mult >> mat_size >> n_omp)) break;
		}

		// Start PAPI
		ret = PAPI_start(EventSet);
		if (ret != PAPI_OK) cout << "ERRO: Start PAPI" << endl;

		// Calculation
		double time = OnMult(mat_size, line_mult, n_omp);

		// Stop PAPI
		ret = PAPI_stop(EventSet, values);
		if (ret != PAPI_OK) cout << "ERRO: Stop PAPI" << endl;
			
		// Output
		//printf("Time: %3.3f seconds\n", time);
		//printf("L1 DCM: %lld \n",values[0]);
		//printf("L2 DCM: %lld \n",values[1]);
		cout << line_mult << " ";
		cout << mat_size << " ";
		cout << n_omp << " ";
		cout << time << " ";
		cout << values[0] << " ";
		cout << values[1] << " ";
		cout << endl;
	} while (argc == 1);


	// Teardown PAPI
	ret = PAPI_reset( EventSet );
	if ( ret != PAPI_OK )
		std::cout << "FAIL reset" << endl; 


		ret = PAPI_remove_event( EventSet, PAPI_L1_DCM );
		if ( ret != PAPI_OK )
			std::cout << "FAIL remove event" << endl; 

		ret = PAPI_remove_event( EventSet, PAPI_L2_DCM );
		if ( ret != PAPI_OK )
			std::cout << "FAIL remove event" << endl; 

		ret = PAPI_destroy_eventset( &EventSet );
		if ( ret != PAPI_OK )
			std::cout << "FAIL destroy" << endl;

}
