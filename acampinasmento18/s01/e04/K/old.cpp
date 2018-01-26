#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 5123;

char str[N + 2];

vector<string> vs;

const int M = 112345;

map<char, int> tr[M];
set<ll> hsh[M];

deque<int> ocs[M];
deque<int> good_ocs[M];

int en = 1;
short len[M];

inline void add_word(int &v, string &s) {
	if(!tr[v].count(s[0])) {
		len[en] = len[v] + 1;
		tr[v][s[0]] = en++;
	}
	v = tr[v][s[0]];
}

void add_to_hsh(ll &h, string &s) {
	for(char c : s)
		h = (h * 239 + c) % 1000000007;
}

short sz[M];
short L[M], R[M];
bool bad[M];

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
	int n = vs.size();
	for(i = n - 1; i >= 1; i--) {
		int v = 0;
		string abrev;
		ll h = 0;
		int sz = 0;
		for(int j = i; j < n; j++) {
			sz += int(vs[j].size());
			add_to_hsh(h, vs[j]);
			abrev.pb(vs[j][0]);
			add_word(v, vs[j]);
			hsh[v].insert(h);
			if(all.count(abrev)) bad[v] = true;
			auto it = upper_bound(ocs[v].begin(), ocs[v].end(), j);
			if(it != ocs[v].end()) good_ocs[v].push_front(good_ocs[v][it - ocs[v].begin()] + 1);
			else good_ocs[v].push_front(1);
			ocs[v].push_front(i);
			::sz[v] = sz;
			::L[v] = i;
			::R[v] = j;
		}
	}
	int best = 0;
	int l, r;
	for(i = 0; i < en; i++) {
		if(hsh[i].size() == 1 && !bad[i]) {
			int ef = (sz[i] * good_ocs[i].front()) - (sz[i] + len[i] * good_ocs[i].front()); 
			if(ef > best)
				best = ef, l = L[i], r = R[i];
		}
	}
	printf("%d\n", best);
	if(best) {
		for(i = l; i <= r; i++)
			putchar(toupper(vs[i][0]));
		putchar('\n');
	}
}
