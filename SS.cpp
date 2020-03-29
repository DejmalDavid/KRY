//Cely modul prevzat z https://www.geeksforgeeks.org/primality-test-set-4-solovay-strassen/
//prepsany z int do mzp_class Davidem Dejmalem 29.3.2020

// C++ program to implement Solovay-Strassen 
// Primality Test 
#include <bits/stdc++.h> 
#include <gmp.h>
#include <gmpxx.h>

#define SEED  42424242	//my magic number 
using namespace std; 
namespace SS
{
	


	
// modulo function to perform binary exponentiation 
mpz_class  modulo(mpz_class  base, mpz_class  exponent, mpz_class  mod) 
{ 
	mpz_class  x; 
	x = 1;
	//mpz_init(x);
	//mpz_set_ui(x,1);	
	
	mpz_class  y ; 	
	y=base;
	//mpz_init(y);
	//mpz_set_ui(y,base);
	
	while (exponent > 0) 
	{ 
		if (exponent % 2 == 1) 
			x = (x * y) % mod; 

		y = (y * y) % mod; 
		exponent = exponent / 2; 
	} 

	return x % mod; 
} 

// To calculate Jacobian symbol of a given number 
int calculateJacobian(mpz_class  a, mpz_class  n) 
{ 
	if (a==0) 
		return 0;// (0/n) = 0 

	int ans = 1; 
	if (a < 0) 
	{ 
		a = -a; // (a/n) = (-a/n)*(-1/n) 
		if (n % 4 == 3) 
			ans = -ans; // (-1/n) = -1 if n = 3 (mod 4) 
	} 

	if (a == 1) 
		return ans;// (1/n) = 1 

	while (a!=0) 
	{ 
		if (a < 0) 
		{ 
			a = -a;// (a/n) = (-a/n)*(-1/n) 
			if (n % 4 == 3) 
				ans = -ans;// (-1/n) = -1 if n = 3 (mod 4) 
		} 

		while (a % 2 == 0) 
		{ 
			a = a / 2; 
			if (n % 8 == 3 || n % 8 == 5) 
				ans = -ans; 

		} 

		swap(a, n); 

		if (a % 4 == 3 && n % 4 == 3) 
			ans = -ans; 
		a = a % n; 

		if (a > n / 2) 
			a = a - n; 

	} 

	if (n == 1) 
		return ans; 

	return 0; 
} 

// To perform the Solovay-Strassen Primality Test 
bool solovoyStrassen(mpz_class  p, int iterations, int bits) 
{ 
	if (p < 2) 
		return false; 
	if (p != 2 && p % 2 == 0) 
		return false; 

	for (int i = 0; i < iterations; i++) 
	{ 
		// Generate a random number a 
		mpz_class a;
		//mpz_init(a);
		//mpz_set_ui(a, 0);
		//randP(bits,a);
		a= 654615;
		a = a % (p - 1) + 1; 
		
		
		mpz_class  jacobian; 
		jacobian = (p + calculateJacobian(a, p)) % p;
		
		
		//mpz_init(jacobian);
		//mpz_set_ui(jacobian, ((p + calculateJacobian(a, p)) % p));
		
		mpz_class  mod; 
		mod = (modulo(a, (p - 1) / 2, p));
		//mpz_init(mod);
		//mpz_set_ui(mod, (modulo(a, (p - 1) / 2, p)) );
		
		if ((jacobian==0) || (mod != jacobian)) 
			return false; 
	} 
	return true; 
} 


}

