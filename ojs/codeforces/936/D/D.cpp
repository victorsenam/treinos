#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

struct obs {
	int i, l;
};

int n, ml[3], t;
int m;
obs x[N];
int memo[N][2];

int dp (int i, int l) {
	if (i == -1) return 0;
}

int main () {
	memset(memo, -1, sizeof memo);
	scanf("%d", &n);

	scanf("%d %d %d %d", &n, &ml[1], &ml[2], &t);

	for (int k = 1; k <= 2; k++) {
		for (int i = 0; i < ml[k]; i++) {
			scanf("%d", &x[m].i);
			w[m].l = k;
			m++;
		}
	}

	sort(x, x+m, [] (obs a, obs b) { return a.i < b.i; });
	int ss = m;
	m = 0;
	for (int i = 0; i < ss; i++) {
		if (m && x[i].i == x[m-1].i)
			x[m-1].l += x[i].l;
		else
			x[m++] = x[i];
	}

	
}
