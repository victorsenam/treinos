#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int a[11234];
int q[11234];

int main () {
	int i, n;
	for(n = 0; scanf("%d", &a[n]) != EOF; n++);
	vector<int> p;
	for(i = n - 1; i >= 0; i--)
		p.insert(p.begin() + a[i], i);
	for(i = 0; i < n; i++)
		q[p[i]] = i;
	for(i = 0; i < n; i++) {
		int j;
		for(j = 0; q[j] != i; j++);
		int ct = 0;
		while(j--) ct += (q[j] > i);
		printf("%d ", ct);
	}
	putchar('\n');
}
