#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n;

struct vec {
	ll x, y;

	vec operator - (vec o) {
		return vec({x-o.x,y-o.y});
	}
	ll operator * (vec o) {
		return x*o.y - y*o.x;
	}
};

const int N = 50007;
vec v[N];

int main () {
	scanf("%d", &n);
	ll res = 0;
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &v[i].x, &v[i].y);
	}

	for (int i = 2; i < n; i++) {
		res += (v[i] - v[0])*(v[i-1] - v[0]);
	}

	printf("%.3f\n", double(abs(res))/2);
}
