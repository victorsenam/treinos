#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 65537;

int v[N];
int n;

int main () {
	scanf("%d", &n);
	bool ev = (n%2 == 0);

	for (int i = 0; i < n; i++) {
		scanf("%d", &v[i]);
	}

	sort(v, v+n);
	n = unique(v,v+n) - v;
	if (ev) {
		for (int i = n-1; i >= 0; i--)
			printf("%d\n", v[i]);
	} else {
		for (int i = 0; i < n; i++)
			printf("%d\n", v[i]);
	}
}
