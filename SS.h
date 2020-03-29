// my_class.h
#ifndef SS_H // include guard
#define SS_H

namespace SS
{
	// modulo function to perform binary exponentiation 
	mpz_class modulo(long long base, long long exponent,long long mod); 


	// To calculate Jacobian symbol of a given number 
	int calculateJacobian(long long a, long long n); 


	// To perform the Solovay-Strassen Primality Test 
	bool solovoyStrassen(mpz_class p, int iterations, int bits);

}

#endif 