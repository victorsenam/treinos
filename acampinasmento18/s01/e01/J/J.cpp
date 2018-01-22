#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef int tA;
typedef null_type tB;
typedef tree<tA, tB, less<tA>, rb_tree_tag, tree_order_statistics_node_update> ord_set;

const int N = 1123456;
int tr[N << 2];

void build(int i, int l, int r) {
	tr[i] = (r - l + 1);
	if(l == r) return;
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
}

// 1 index
int get_k(int i, int l, int r, int k) {
	if(l == r) return l;
	int m = (l + r) / 2;
	if(tr[2 * i] >= k) return get_k(2 * i, l, m, k);
	else return get_k(2 * i + 1, m + 1, r, k - tr[2 * i]);
}

void sub1(int i, int l, int r, int q) {
	tr[i]--;
	if(l == r) return;
	int m = (l + r) / 2;
	if(q <= m) sub1(2 * i, l, m, q);
	else sub1(2 * i + 1, m + 1, r, q);
}


int main () {
	int i, j; int n, p;
	scanf("%d %d", &n, &p);
	build(1, 0, n - 1);
	i = 0;
	for(j = 0; j < n - 1; j++) {
		i = (((i - 1) + p) % (n - j) + (n - j)) % (n - j);
		int k = get_k(1, 0, n - 1, i + 1);
		sub1(1, 0, n - 1, k);
	}
	printf("%d\n", get_k(1, 0, n - 1, 1) + 1);
}
