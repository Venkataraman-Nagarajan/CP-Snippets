typedef long long ll;
const ll N = 2 * 1e5 + 25;

ll par[N], sz[N];
ll comp; // init comp = no of nodes provided

void make(ll n) {
	for(ll i=1;i<=n;i++) {
		par[i] = i;
		sz[i] = 1;
	}
}

ll find(ll x) {
	return x == par[x]?x:par[x] = find(par[x]);
}

void merge(ll x, ll y) {
	ll u = find(x);
	ll v = find(y);

	if(u == v) return;

	if(sz[u] < sz[v]) swap(u,v);
	sz[u] += sz[v];
	par[v] = u; 
	comp--;
}
