#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

const int N = (1<<14);
int n, m;

uint8_t M_[2][1 << 11];

inline int M(int i, int j) {
	return ((M_[i][j / 8] >> (j & 7)) & 1);
}
inline void clearM(int i, int j) {
	M_[i][j / 8] ^= (1 << (j & 7));
}

int val[128];

inline bool valid(int i, int j) {
	return i >= 0 && i < n && j >= 0 && j < m;
}

int di[] = {1, -1, 0, 0};
int dj[] = {0, 0, -1, 1};

int inv[16];

int hd[N], nx[N];
int mrk[2][N];
int ct;
int k, c;

void dfs (int j) {
	if (j < 0 || j >= m) return;
	if (mrk[k][j] == -2 || mrk[k][j] == c) return;
	
	mrk[k][j] = c;
	dfs(j+1);
	dfs(j-1);

	int hd = mrk[!k][j];
	if (hd != -2) {
		ct--;
		for(int x = hd; x != -1; x = nx[x])
			mrk[!k][x] = -2;
		for(int x = hd; x != -1; x = nx[x])
			dfs(x);
	}
}

int main() {
	int i = 0, j; char c;
	scanf("%d %d", &n, &m);
	for(char c : "0123456789ABCDEF")
		val[c] = i++;
	for(i = 0; i < 16; i++) {
		for(j = 0; j < 4; j++)
			inv[i] |= (((i >> j) & 1) << (3 - j));
	}

	ct = 0;
	for (int i = 0; i < m; i++)
		mrk[1][i] = -2;
	for (int j = 0; j < m; j++) {
		nx[j] = -1;
	}

	for(i = 0; i < n; i++) {
		k = (i&1);
		for(j = 0; j < m / 4; j++) {
			while(isspace(c = getchar()));
			if(j & 1) M_[k][j / 2] |= (inv[val[c]] << 4);
			else M_[k][j / 2] = inv[val[c]];
		}

		for (int j = 0; j < m; j++) {
			if (M(k,j) == 1)
				mrk[k][j] = -1;
			else
				mrk[k][j] = -2;
		}

		for (int j = 0; j < m; j++) {
			if (mrk[k][j] == -1) {
				ct++;
				::c = j;
				dfs(j);
			}
		}

		for (int j = 0; j < m; j++) {
			nx[j] = -1;
		}

		for (int j = 0; j < m; j++)
			if (mrk[k][j] >= 0 && mrk[k][j] != j) {
				nx[j] = nx[mrk[k][j]];
				nx[mrk[k][j]] = j;
			}
	}

	printf("%d\n", ct);
}
