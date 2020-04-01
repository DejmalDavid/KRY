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

mpz_class modInverse(mpz_class a, mpz_class m) 
{ 
    a = a%m; 
    for (mpz_class x=1; x<m; x++) 
       if ((a*x) % m == 1) 
          return x; 
} 

mpz_class gcd_recursive(mpz_class a, mpz_class b)
{
    if (b!=0)
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


mpf_class myRand(int bits)
{
	if(bits%2==0) return rr.get_z_bits(((bits/2)));
	else return rr.get_z_bits(((bits/2)+1));
}




int main(int argc, char **argv) {
	
	int B;
	mpz_class P;
	mpz_class Q;
	mpz_class n;
	mpz_class e;
	mpz_class d;
	
	mpz_t N;
	mpz_t E;
	mpz_t D;
	mpz_t M;
	mpz_t C;
	
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
					//cout<<"G1:"<<B<<endl;
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
				//cout<<"parametr G"<<B<<endl;	
				P=myRand(B);
				Q=myRand(B);
				//cout<<"rand:"<<P<<endl;
				//cout<<"rand:"<<Q<<endl;
				
				while(Q%2==0)
				{
					Q=myRand(B);
				}
				while(P%2==0)
				{
					P=myRand(B);
				}
				
				
				//cout<<"Jsem lichy:"<<P<<endl;
				while(solovoyStrassen(P, 100,B)==false)
				{
					P=P+2;
				}
				//cout<<"Prime:"<<P<<endl;
				
				
				//cout<<"Jsem lichy:"<<Q<<endl;
				while(solovoyStrassen(Q, 100,B)==false)
				{
					Q=Q+2;
				}
				
				//cout<<"Prime:"<<Q<<endl;
					
				n = P * Q;	//go

				//cout<<"N:"<<n<<endl;
				//cout<<"N:"<<hex<<n<<endl;
				
				mpz_class phi;
				phi = (P-1)*(Q-1);
				
				//cout<<"PHI:"<<phi<<endl;
				
				e=3;			
				while(gcd_recursive(e,phi)!=1) {
					 e++;
				}
				
				//cout<<"E:"<<e<<endl;
				//cout<<"E:"<<hex<<e<<endl;
				
				
				d = modInverse(e,phi);
		
				
				//cout<<"D:"<<d<<endl;
				
				//cout<<"D:"<<hex<<d<<endl;

				cout<<hex<<"0x"<<P<<" 0x"<<Q<<" 0x"<<n<<" 0x"<<e<<" 0x"<<d<<endl;
				
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
				cout<<"0x"<<hex<<M<<endl;
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