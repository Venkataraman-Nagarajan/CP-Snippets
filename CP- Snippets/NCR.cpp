ll NCR(ll n, ll r) {
	if (n < r ) return 0;
	if (r == 0) return 1;
	if (r > n / 2) return NCR(n, n - r);
	ll res = 1;
	for (ll k = 1; k <= r; ++k) {
		res *= n - k + 1;
		res /= k;
	}
	return res;
}

//////////////////////////////////////////////////

ll ncr(ll n, ll r) {
	return f[n] * fastMod(f[r]) % MOD * fastMod(f[n - r]) % MOD;
}

// f[x] - denotes factorial of x