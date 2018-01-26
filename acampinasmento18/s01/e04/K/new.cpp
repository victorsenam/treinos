#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2003;
const int M = N*N;

map<string,int> mp;
string text[N];
int tt;
char str[N+N];
map<int,int> trie[2][N];
int es[2];
int cnt[M], fis[M], qt[M], siz[M], las[M], occ[M];
bool bad[M];

void add (int k, int & u, int v) {
	if (!trie[k][u][v])
		v = trie[k][u][v];
	v = trie[k][u][v] = es[k]++;
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("kina.in", "r", stdin);
	freopen("kina.out", "w", stdout);
#endif

	int n = 0;
	while (true) {
		fgets(str+n, N, stdin);
		if (feof(stdin)) break;
		n += strlen(str+n);
	}
	str[n] = 0;

	n = 0;
	for (int i = 0; !i || str[i-1]; i++) {
		if (!isalpha(str[i])) {
			if (text[tt].size()) {
				int sz = mp.size();
				mp[text[tt++]] = sz;
			}
		} else {
			text[tt].pb(str[i]);
		}
	}
	
	es[0] = es[1] = 1;
	for (int i = 0; i < tt; i++) {
		int seq = 0;
		int abr = 0;
		int sizz = 0;
		for (int j = i; j < tt; j++) {
			sizz += text[j].size();
			add(0,seq,text[j][0]);
			add(1,abr,mp[text[j]]);
			if (cnt[abr] == 0) { fis[abr] = i; qt[abr] = j - i + 1; siz[abr] = sizz; }
			cnt[seq]++; cnt[abr]++;
			if (cnt[seq] != cnt[abr]) {
				bad[abr] = 1;
			} else if (las[abr] <= i) {
				occ[abr]++;
				las[abr] = j+1;
			}
		}
	}

	int best = 0;
	int ba = 0;
	for (int i = 1; i < es[1]; i++) {
		int ef = (siz[i]*occ[i]) - (siz[i] + qt[i]*occ[i]);
		if (!bad[i] && ef > best) {
			best = ef;
			ba = i;
		}
	}

	printf("%d\n", best);
	for (int i = fis[ba]; i < fis[ba] + qt[ba]; i++)
		printf("%c", text[i][0]);
	printf("\n");
}
