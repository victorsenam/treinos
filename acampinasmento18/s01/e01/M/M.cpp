#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

pii get() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	a = (c - a) * (c - a) + (d - b) * (d - b);
	int mx = 1;
	for(int i = 2; i * i <= a; i++)
		if((a % (i * i)) == 0)
			mx = i;
	return pii(mx, a / (mx * mx));
}

int main () {
	pii A = get();
	pii B = get();
	if(A.second != B.second) puts("NO");
	else {
		puts("YES");
		printf("%.6f\n", __gcd(A.first, B.first) * sqrt(A.second));
	}
}
