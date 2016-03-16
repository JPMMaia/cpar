all: tester prog_cpp prog_java

tester:
	g++ tester.cpp -o tester.o 
	
prog_cpp:
	g++ prog_cpp.cpp -o prog_cpp.o -l papi -fopenmp -O3
	
prog_java:
	javac prog_java.java

clean:
	\rm *.o *.class *.out

test_cpp_omp:
	echo "C++ with OMP \n\n\n"
	./tester.o 1 8 600 3000 400 | ./prog_cpp.o
	
test_cpp_vs_java:
	echo C++
	./tester.o 1 0 600 3000 400 | ./prog_cpp.o
	echo Java
	./tester.o 1 0 600 3000 400 | java prog_java


