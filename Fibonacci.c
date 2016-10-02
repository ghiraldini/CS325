#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// --------------------------------------------------------- //
// Title:     Fibonacci Series
// Author:    Jason Ghiraldini
// Term:      Fall 2016
// Class:     CS 325 - Analysis of Algorithms
// Input:     User inputs the number of the sequence
// Output:    Code computes Fibonacci number
// --------------------------------------------------------- //

unsigned long fib_rec(unsigned long);
unsigned long fib_iter(unsigned long);

int main(int argc, char* argv[]){
	unsigned long fibIdx = strtol(argv[1], NULL, 10);
	//printf("Fibonacci Number: %lu\n", fib_rec(fibIdx));
	printf("Fibonacci Number: %lu\n", fib_iter(fibIdx));

	return 0;
}

// -------------------------------------- //
// Find Fibonacci Number recursively
// -------------------------------------- //
unsigned long fib_rec(unsigned long n){
	if(n == 0){
		return 0;
	}else if(n == 1){
		return 1;
	}else{
		return (fib_rec(n-1) + fib_rec(n-2));
	}
}

// -------------------------------------- //
// Find Fibonacci Number Iteratively
// -------------------------------------- //
unsigned long fib_iter(unsigned long n){
	unsigned long fib = 0;
	int a = 1;
	int t = 0;
	int k = 0;
	for(k = 0; k < n; k++){
		t = fib + a;
		a = fib;
		fib = t;
	}
	return fib;
}
