#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace pb_ds;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 400007;

typedef __gnu_pbds::tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

using namespace std;

ordered_set mp;
int n;
int q, a;

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &q, &a);
		if (q == 1)
			mp.insert(a);
		else
			printf("%d\n", mp.order_of_key(a));
	}
}
