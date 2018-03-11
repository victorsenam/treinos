#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<int,int> pii;
#define pb push_back

const int N = 1e5;
map<pii, ll> mp;
ll k;

int main () {
	int n;
	scanf("%d", &n);

	int a, k;
	ll r = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &a, &k);
		while (a > 0 && a%k != 0) a -= a/k + 1;
		//ll rr = r;
		if (a > 0) r ^= a/k;
		//cout << (r^rr) << endl;
	}
	printf("%s\n", r?"Takahashi":"Aoki");
}
