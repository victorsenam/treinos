#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double dbl;

int main () {
	int n, x; char op;
	scanf("%d", &n);
	map<int, int> f;
	while(n--) {
		scanf(" %c %d", &op, &x);
		if(op == '-') {
			if(--f[x] == 0) f.erase(x);
		} else f[x]++;
		int i = 0;
		dbl cur = 0;
		dbl bot = 1;
		dbl tot = 1;
		bool bad = false;
		for(auto e : f) {
			if(++i > 60) { bad = true; break; }
			bot /= (e.second + 1);
			tot *= (e.second + 1);
			cur += e.second * bot * dbl(e.first);
		}
		if(!bad) cur *= (tot / (tot - 1));
		printf("%.10f\n", double(cur));
	}
}
