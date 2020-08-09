long long gcd(long long m,long long n) {
	if(!n) return m;
	return gcd(n,m%n);
}

long long GCD(long long m, long long n) {
	return (m>=n)?return gcd(m,n):gcd(n,m);
}

// call GCD