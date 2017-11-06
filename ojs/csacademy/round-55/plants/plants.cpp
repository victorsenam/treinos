#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 107;

int n, m;
int t[N];

int main () {
	scanf("%d %d", &m, &n);

	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);
		t[a]++;
	}

	for (int i = 1; i < N; i++)
		t[i] += t[i-1];

	for (int i = 0; i < m; i++) {
		int a,b;
		scanf("%d %d", &a, &b);
		printf("%d\n", t[b] - t[a-1]);
	}
}
