typedef long long ll;
const ll MOD = 1e9 + 7;

ll tree[200000];
ll a[10000];

ll op(ll a, ll b) {
	return a+b;
	// return max(a,b);
	// return min(a,b);
	// return a*b

	// add %MOD if necessary
}

void build(ll start=1 , ll end=n , ll node=1) {
	if (start == end) {
		tree[node] = a[start];
	}
	else {
		ll mid = (start + end) / 2;
		build(start, mid, 2 * node);
		build(mid + 1, end, 2 * node + 1);
		tree[node] = op(tree[2 * node] , tree[2 * node + 1]);
	}
}

void update(ll indx, ll val, ll start = 1 , ll end = n , ll node = 1) {
	if (start == end) {
		a[indx] = val;
		tree[node] = val;
	}
	else {
		ll mid = (start + end) / 2;
		if (start <= indx && indx <= mid) update( indx, val, start, mid, 2 * node);
		else 							update(indx, val, mid + 1, end, 2 * node + 1);
		tree[node] = op(tree[2 * node] , tree[2 * node + 1]);
	}
}

ll query(ll l, ll r, ll start = 1, ll end = n , ll node = 1) {
	if (r < start || end < l) {
		return 0; // sum;
		// return LLONG_MAX // min
		// return LLONG_MIN // max
		// return 1 // multiply 
	}
	else if (l <= start && end <= r) {
		return tree[node];
	}
	else {
		ll mid = (start + end) / 2;
		ll p1 = query(l, r, start, mid, 2 * node);
		ll p2 = query(l, r, mid + 1, end, 2 * node + 1);
		return op(p1 , p2);
	}
}