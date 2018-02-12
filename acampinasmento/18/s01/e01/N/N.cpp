#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e4+4;
bitset<N+N> reach[N];
int n, a;
int v[N];
bool rev[N];
queue<pii> qu;

void go (int n, int c) {
	if (n == 1) return;
	if (reach[n-1][c-v[n-1]+N]) {
		rev[n-1] = 0;
		go(n-1, c-v[n-1]);
	} else {
		rev[n-1] = 1;
		go(n-1, c+v[n-1]);
	}
}

int main () {
	scanf("%d %d", &n, &a);
	
	for (int i = 0; i < n; i++)
		scanf("%d", &v[i]);

	qu.push(pii(v[0],1));
	reach[1][v[0]+N] = 1;
	while (!qu.empty()) {
		pii p = qu.front();
		qu.pop();

		if (p.second == n) continue;
		for (ll d : {p.first - v[p.second], p.first + v[p.second]}) {
			if (reach[p.second+1][d+N]) continue;
			reach[p.second+1][d+N] = 1;
			qu.push(pii(d,p.second+1));
		}
	}

	for (int d = 0; d < N+N; d++) {
		if (a-d > -N && reach[n][a-d+N]) {
			printf("%d\n", a-d);
			go(n,a-d);
			break;
		} else if (a+d < N && reach[n][a+d+N]) {
			printf("%d\n", a+d);
			go(n,a+d);
			break;
		}
	}

	printf("%d", v[0]);
	for (int i = 1; i < n; i++)
		printf("%c%d", rev[i]?'-':'+', v[i]);
	printf("\n");
}
