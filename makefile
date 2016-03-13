all: tester prog_cpp prog_java

tester:
	g++ tester.cpp -o tester.o 
	
prog_cpp:
	g++ prog_cpp.cpp -o prog_cpp.o -l papi -fopenmp -O3
	
prog_java:
	javac prog_java.java

clean:
	\rm *.o *.class *.out

test:
	make all
	echo C++
	./tester.o | ./prog_cpp.o
	echo Java
	./tester.o | java prog_java	
	
test_file:
	make all
	echo C++ > output.out
	./tester.o | ./prog_cpp.o >> output.out
	echo Java >> output.out
	./tester.o | java prog_java >> output.out


