#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

char c;
inline void rd(int &x) {
	while(isspace(c = getchar_unlocked()));
	x = (c - '0');
	while(isdigit(c = getchar_unlocked()))
		x = (x << 3) + (x << 1) + (c - '0');
}

int A[3002][3002];
int freq[112345];
int cur, best;
ll tot;

inline void add(int x) {
	if(freq[x]++ == 0)
		cur++;
	//printf("add %d cur %d\n", x, cur);
}

inline void rem(int x) {
	if(--freq[x] == 0)
		cur--;
	//printf("rem %d cur %d\n", x, cur);
}

int main () {
	int i, j, k, g, n, m;
	rd(n); rd(m); rd(k);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			rd(A[i][j]);
	for(i = 0; i < k; i++)
		for(j = 0; j < k; j++)
			add(A[i][j]);
	tot = cur;
	best = cur;
	//printf("at(0, 0) + %d = cur %d\n", k, cur);
	for(i = 0; i + k - 1 < n; i++) {
		if(i & 1) {
			for(j = m - 1 - k; j >= 0; j--) {
				for(g = 0; g < k; g++) {
					rem(A[i + g][j + k]);
					add(A[i + g][j]);
				}
				//printf("at(%d, %d) + %d = cur %d\n", i, j, k, cur);
				best = max(best, cur);
				tot += cur;
			}
			if(i + k < n) {
				for(g = 0; g < k; g++) {
					rem(A[i][g]);
					add(A[i + k][g]);
				}
				best = max(best, cur);
				tot += cur;
				//printf("at(%d, 0) + %d = cur %d\n", i + 1, k, cur);
			}
		} else {
			for(j = 0; j + k < m; j++) {
				for(g = 0; g < k; g++) {
					rem(A[i + g][j]);
					add(A[i + g][j + k]);
				}
				//printf("at(%d, %d) + %d = cur %d\n", i, j + 1, k, cur);
				best = max(best, cur);
				tot += cur;
			}
			if(i + k < n) {
				for(g = 0; g < k; g++) {
					rem(A[i][m - 1 - g]);
					add(A[i + k][m - 1 - g]);
				}
				best = max(best, cur);
				tot += cur;
				//printf("at(%d, %d) + %d = cur %d\n", i + 1, m - k, k, cur);
			}
		}
	}
	printf("%d %lld\n", best, tot);
}
