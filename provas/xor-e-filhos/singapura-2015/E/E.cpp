#include <bits/stdc++.h>

using namespace std;

const int N = 14;
const int K = (1<<N);
typedef unsigned int ui;
typedef pair<int, int> pii;

int v[N];
pii memo[K][301];
int visi[K][301], turn;
int n, p;

pair<int, int> pd (ui mask, int t) {
	if (t > 300 || __builtin_popcount(mask) == n)
		return pii(0,0);
	
	pii & me = memo[mask][t];
	if (visi[mask][t] == turn)
		return me;
	visi[mask][t] = turn;
	
	me = pii(0,0);

	for (int i = 0; i < n; i++) {
		if (mask&(1<<i)) continue;
		if (t+v[i] > 300) continue;
		pii aux = pd(mask|(1<<i), t+v[i]);
		aux.first++;
		aux.second -= v[i]+t;
		me = max(me, aux);
	}
	
	return me;
}

int main () {
	while (scanf("%d %d", &n, &p) != EOF && ++turn) {
		for (int i = 0; i < n; i++)
			scanf("%d", v+i);
		
		pii res = pd((1<<p), v[p]);
		if (v[p] <= 300) printf("%d %d\n", res.first+1, -res.second+v[p]);
		else printf("0 0\n");
	}
}
