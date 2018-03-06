#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int n;
pii v[N];

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &v[i].first, &v[i].second);
	}

	sort(v[i], v[i] + n,  [] (pii a, pii b) { return a.first + a.second < b.first + b.second; });
}
