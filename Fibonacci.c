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

int fib_rec(int);
int fib_iter(int);

int main(int argc, char* argv[]){
	clock_t begin = clock();

	int fibIdx = strtol(argv[1], NULL, 10);
	printf("Fibonacci Number: %i\n", fib_rec(fibIdx));	
	
	clock_t end = clock();
	clock_t elapsed_t = end-begin;
	double elapsed_time = elapsed_t / CLOCKS_PER_SEC;
	printf("Time spent: %f\n", elapsed_time);

	return 0;
}

// -------------------------------------- //
// Find Fibonacci Number recursively
// -------------------------------------- //
int fib_rec(int n){
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

int fib_iter(int n){
	int fib = 0;
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
	


