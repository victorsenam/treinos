#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 5123;

char str[N + 2];

vector<string> vs;

const int M = 4000000 + 9;

map<char, int> tr[M];
map<string, int> t2[M];
int hsh[M];

short lst[M];

int en = 1;
short oc[M];
bitset<M> bad;
int en2 = 1;

inline void add_word(int &v, string &s) {
	if(!tr[v].count(s[0])) {
		tr[v][s[0]] = en++;
	}
	v = tr[v][s[0]];
}

inline void add_2(int &v, string &s) {
	if(!t2[v].count(s)) {
		t2[v][s] = en2++;
	}
	v = t2[v][s];
}

void add_to_hsh(ll &h, string &s) {
	for(char c : s)
		h = (h * 239 + c) % 1000000007;
	h = (h * 239 + '!') % 1000000007;
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("kina.in", "r", stdin);
	freopen("kina.out", "w", stdout);
#endif
	fread(str, 1, N, stdin);
	int i = 0;
	set<string> all;
	while(str[i]) {
		while(str[i] && !isalpha(str[i])) i++;
		if(!str[i]) break;
		string s;
		while(isalpha(str[i]))
			s.pb(tolower(str[i++]));
		vs.pb(s);
		all.insert(s);
	}
	memset(lst, -1, sizeof lst);
	int n = vs.size();
	for(i = 0; i < n; i++) {
		int v = 0;
		string abrev;
		int sz = 0;
		int v2 = 0;
		for(int j = i; j < n; j++) {
			sz += int(vs[j].size());
			abrev.pb(vs[j][0]);
			add_word(v, vs[j]);
			add_2(v2, vs[j]);
			if(hsh[v] && (hsh[v] != v2)) {
				bad[v] = 1;
				//printf("bad[%s] = true\n", abrev.c_str());
			}
			hsh[v] = v2;
			if(lst[v] >= i) continue;
			lst[v] = j;
			oc[v]++;
		}
	}
	int best = 0;
	int l, r;
	for(i = 0; i < n; i++) {
		int v = 0;
		string abrev;
		int sz = 0;
		for(int j = i; j < n; j++) {
			sz += int(vs[j].size());
			abrev.pb(vs[j][0]);
			add_word(v, vs[j]);
			if(bad[v] || all.count(abrev)) continue;
			int ef = (sz * oc[v]) - (sz + (j - i + 1) * oc[v]);
			if(ef > best) {
				best = ef;
				l = i;
				r = j;
			}
		}
	}
	printf("%d\n", best);
	if(best) {
		for(i = l; i <= r; i++)
			putchar(toupper(vs[i][0]));
		putchar('\n');
	}
}
