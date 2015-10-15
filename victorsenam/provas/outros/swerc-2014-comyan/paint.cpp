#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll modn = 1000000007;
ll mod(ll x) { return x % modn; }
ll pot[4000009];
ll hh[2003][2003];
int main() {
	int i, j;
	int h1, w1, h2, w2;
	char c;
	pot[0] = 1;
	for(i = 1; i < 4000009; i++)
		pot[i] = mod(pot[i - 1] * 5ll);
	while(scanf("%d %d %d %d", &h1, &w1, &h2, &w2) != EOF) {
		ll h = 0;
		for(i = 0; i < h1; i++)
			for(j = 0; j < w1; j++) {
				scanf(" %c", &c);
				h = mod(h + pot[i * w2 + j] * ((c == 'x') + 1));
			}
		for(i = 0; i < h2; i++) {
			for(j = 0; j < w2; j++) {
				scanf(" %c", &c);
				hh[i][j] = mod(pot[i * w2 + j] * ((c == 'x') + 1));
			}
		}
		for(i = 0; i < h2; i++) {
			for(j = 0; j < w2; j++) {
				if(i > 0) hh[i][j] += hh[i - 1][j];
				if(j > 0) hh[i][j] += hh[i][j - 1];
				if(i > 0 && j > 0) hh[i][j] += modn - hh[i - 1][j - 1];
				hh[i][j] = mod(hh[i][j]);
			}
		}
		int tot = 0;
		for(i = 0; i + h1 - 1 < h2; i++)
			for(j = 0; j + w1 - 1 < w2; j++) {
				ll acc = hh[i + h1 - 1][j + w1 - 1];
				if(i > 0) acc += modn - hh[i - 1][j + w1 - 1];
				if(j > 0) acc += modn - hh[i + h1 - 1][j - 1];
				if(i > 0 && j > 0) acc += hh[i - 1][j - 1];
				if(mod(acc) == mod(h * pot[i * w2 + j])) tot++;
			}
		printf("%d\n", tot);	
	}
}
