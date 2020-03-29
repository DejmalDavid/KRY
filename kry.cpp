#include<iostream>
#include<math.h>
#include <sstream>
#include <getopt.h>
#include <string.h>
#include <gmp.h>
#include <gmpxx.h>

#include "SS.h"



using namespace std;
using namespace SS;

	unsigned long int seed = time(NULL);
	gmp_randclass rr(gmp_randinit_default);

//cte string v hexa a uklada do mpz_t
//pri selhani false
bool readNumber( char *argv,mpz_t number)
{
	int flag;
	string tmp (argv);
	tmp.erase(0, 2); //skip "0x" 
	//cout<<"vstup string:"<<tmp<<endl;
	flag = mpz_set_str(number,tmp.c_str(), 16);
	//cout<<"number:"<<number<<endl;
	if(flag==-1) return false;
	else return true;
}


// find gcd
int gcd(int a, int b) {
   int t;
   while(1) {
      t= a%b;
      if(t==0)
      return b;
      a = b;
      b= t;
   }
}


unsigned gcd_recursive(unsigned a, unsigned b)
{
    if (b)
        return gcd_recursive(b, a % b);
    else
        return a;
}

/*
void randP(int bits,mpz_t result)
{
			
	gmp_randstate_t state;
	gmp_randinit_default (state);
	gmp_randseed_ui ( state, SEED );
	mpz_urandomb ( result, state, bits );
}

*/


mpf_class randP(int bits)
{
	
	return rr.get_z_bits(bits);
}




int main(int argc, char **argv) {
	
	int B;
	mpz_class P;
	mpz_t Q;
	mpz_t N;
	mpz_t E;
	mpz_t D;
	mpz_t M;
	mpz_t C;
	
	mpz_init(Q);
	mpz_set_ui(Q,0);
	mpz_init(N);
	mpz_set_ui(N,0);
	mpz_init(E);
	mpz_set_ui(E,0);
	mpz_init(D);
	mpz_set_ui(D,0);
	mpz_init(M);
	mpz_set_ui(M,0);
	mpz_init(C);
	mpz_set_ui(C,0);
	
//-------------ZPRACOVANI ARGUMENTU	--------------------

	char lastOpt='x';

	if(argc%2==0)	//pouze lichy pocet parametru povolene jsou 3/5
	{
		fprintf(stderr,"Spatny pocet argumentu!");
		return 1;
	}


	//cout<<argv[1]<<argc<<endl;
 	for(int i=1;i<argc;i++)
	{
		//cout<<i<<endl;
		//zkontroluje prepinace
		if(strcmp(argv[i],"-g")==0)
		{
			lastOpt='g';
			continue;
		}
		if(strcmp(argv[i],"-e")==0)
		{
			lastOpt='e';
			continue;
		}
		if(strcmp(argv[i],"-d")==0)
		{
			lastOpt='d';
			continue;
		}
		if(strcmp(argv[i],"-b")==0)
		{
			lastOpt='b';
			continue;
		}
			
		//cout<<lastOpt<<endl;
		//propoji parametry
		switch(lastOpt)
		{
			case 'x':
				fprintf(stderr,"\nChybne zadane parametry!");
				return 1;

			case 'g':	//prekopiruje argument do potrebne promene
			{
				if(i == 2) 
				{
					string tmp (argv[i]);
					istringstream(tmp) >> B;
					cout<<"G1:"<<B<<endl;
				}
			if(i > 2){ fprintf(stderr,"Prepinac g musi obsahova prave 1 argument: B");	 return 1;}			
				break;
			}
			case 'e':
			{
				if(i == 2) 
				{
					if(readNumber(argv[i],E)==false){fprintf(stderr,"Problem pri zpracovavani parametru"); return 1;}
				}
				if(i == 3)
				{
					if(readNumber(argv[i],N)==false){fprintf(stderr,"Problem pri zpracovavani parametru"); return 1;}
				}
				if(i == 4)
				{
					if(readNumber(argv[i],M)==false){fprintf(stderr,"Problem pri zpracovavani parametru"); return 1;}
				}				
				if(i > 4){ fprintf(stderr,"Prepinac e musi obsahova prave 3 argumenty: E N M");	return 1;}
				break;
			}
			case 'd':
			{	
				if(i == 2) 
				{
					if(readNumber(argv[i],D)==false){fprintf(stderr,"Problem pri zpracovavani parametru"); return 1;}
				}
				if(i == 3)
				{
					if(readNumber(argv[i],N)==false){fprintf(stderr,"Problem pri zpracovavani parametru"); return 1;}
				}
				if(i == 4)
				{
					if(readNumber(argv[i],C)==false){fprintf(stderr,"Problem pri zpracovavani parametru"); return 1;}
				}	
				if(i > 4){ fprintf(stderr,"Prepinac d musi obsahova prave 3 argumenty: D N C");	return 1;}
				break;
			}
			case 'b':
			{
				if(i == 2) 
				{
					if(readNumber(argv[i],E)==false){fprintf(stderr,"Problem pri zpracovavani parametru"); return 1;}
				}
				if(i == 3)
				{
					if(readNumber(argv[i],N)==false){fprintf(stderr,"Problem pri zpracovavani parametru"); return 1;}
				}
				if(i == 4)
				{
					if(readNumber(argv[i],C)==false){fprintf(stderr,"Problem pri zpracovavani parametru"); return 1;}
				}	
				if(i > 4) {fprintf(stderr,"Prepinac b musi obsahova prave 3 argumenty: E N C");	return 1;}
				break;
			}
		}

	}
  
switch(lastOpt)
		{
			case 'x':
				fprintf(stderr,"\nChybne zadane parametry!");
				return 1;

			case 'g':	//prekopiruje argument do potrebne promene
			{
				if(B==0) { fprintf(stderr,"Prepinac g musi obsahova prave 1 argument: B");	 return 1;}				
				break;
			}
			case 'e':
			{	
				if((E==0) || (N==0) || (M==0)) { fprintf(stderr,"Prepinac e musi obsahova prave 3 argumenty: E N M");	return 1;}	
				break;
			}
			case 'd':
			{	
				if((D==0) || (N==0) || (C==0)){ fprintf(stderr,"Prepinac d musi obsahova prave 3 argumenty: D N C");	return 1;}
				break;
			}
			case 'b':
			{
				if((E==0) || (N==0) || (C==0)){fprintf(stderr,"Prepinac b musi obsahova prave 3 argumenty: E N C");	return 1;}
				break;
			}
		}


//------------- KONEC ARGUMENTU ------------------------
	
	switch(lastOpt)
		{
			case 'g':	//prekopiruje argument do potrebne promene
			{
				rr.seed(seed);
				cout<<"parametr G"<<B<<endl;	
				P=randP(B);
				cout<<"rand:"<<P<<endl;
				
				/*
				if (solovoyStrassen(P, 100,B))
				{cout<<"Prime"; }
				else 
				{cout<<"Composite";}
			*/
				while(P%2==0)
				{
					P=randP(B);
				}
				
				cout<<"Jsem lichy:"<<P<<endl;
				while(solovoyStrassen(P, 100,B)==false)
				{
					P=P+2;
				}
				
				cout<<"Prime:"<<P;
					



				return 0;
			}
			case 'e': //encryption verejnym klicem
			{	
				cout<<"parametr E"<<endl;
				//m pow e mod n
				mpz_powm(C,M,E,N);
				cout<<"Cipher:"<<C<<endl;	//TODO
				cout<<"0x"<<hex<<C<<endl;
				return 0;
			}
			case 'd': //decruption privatnim klicem
			{	
				cout<<"parametr D"<<endl;
				//c pow d mod n
				mpz_powm(M,C,D,N);
				cout<<"Mesage:"<<M<<endl;	//TODO
				cout<<"0x"<<hex<<C<<endl;
				return 0;
			}
			case 'b':
			{
				cout<<"parametr B"<<endl;
				return 0;
			}
		}
	

   return 0;

}