
const long long MOD =  1000000007 // prime modulo value 
  
long long exponentiation(long long base, 
                        long long exp) 
{ 
    if (exp == 0) 
        return 1; 
  
    if (exp == 1) 
        return base % MOD; 
  
    long long t = exponentiation(base, exp / 2); 
    t = (t * t) % MOD; 
  
    // if exponent is even value 
    if (exp % 2 == 0) 
        return t; 
  
    // if exponent is odd value 
    else
        return ((base % MOD) * t) % MOD; 
} 


long long fastMod(long long base) {
	return exponentiation(base, MOD-2);
}