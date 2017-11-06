#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n, r, k;

int main () {
	scanf("%d %d %d", &n, &r, &k);

	int a = r;
	int b = n-r;

	int mn, mx;

	printf("%d %d\n", abs(a-k), n-abs(b-k));
}
