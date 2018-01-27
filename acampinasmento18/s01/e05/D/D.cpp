#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int oc[112345];


namespace sf {
const int NS = 12;
const int N = 212345 * 2;

int cn, cd, ns, en = 1, lst;
string S[NS]; int si = -1;
vector<int> sufn[N];

struct node {
	int l, r, si;
	int p, suf;
	map<char, int> adj;
	node() : l(0), r(-1), suf(0), p(0) {}
	node(int L, int R, int S, int P) : l(L), r(R), si(S), p(P) {}
	inline int len() { return r - l + 1; }
	inline int operator[](int i) { return S[si][l+i]; }
	inline int& operator()(char c) { return adj[c]; }
} t[N];

inline int new_node(int L, int R, int S, int P) {
	t[en] = node(L,R,S,P);
	return en++;
}

void add_string(string s) {
	s += '$';
	S[++si] = s;
	sufn[si].resize(s.size() + 1);
	cn = cd = 0;
	int i = 0; const int n = s.size();
	for (int j = 0; j < n; j++) {
		for (; i <= j; i++) {
			if (cd == t[cn].len() && t[cn](s[j]))
				cn = t[cn](s[j]), cd = 0;
			if (cd < t[cn].len() && t[cn][cd] == s[j]) {
				cd++;
				if (j < s.size() - 1) break;
				else {
					if (i) t[lst].suf = cn;
					for(; i<=j;i++) {
						sufn[si][i] = cn;
						cn = t[cn].suf;
					}
				}
			} else if (cd == t[cn].len()) {
				sufn[si][i] = en;
				if(i) t[lst].suf = en; lst=en;
				t[cn](s[j]) = new_node(j,n-1,si,cn);
				cn = t[cn].suf;
				cd = t[cn].len();
			} else {
				int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].si, t[cn].p);
				t[t[cn].p](t[cn][0]) = mid;
				if(ns) t[ns].suf = mid;
				if(i) t[lst].suf = en; lst = en;
				sufn[si][i] = en;
				t[mid](s[j]) = new_node(j,n-1,si,mid);
				t[mid](t[cn][cd]) = cn;
				t[cn].p = mid; t[cn].l += cd;
				cn = t[mid].p;
				int g = cn?j -cd:i+1;
				cn = t[cn].suf;
				while (g<j && g + t[t[cn](S[si][g])].len() <= j)
					cn = t[cn](S[si][g]), g += t[cn].len();
				if (g == j)
					ns = 0, t[mid].suf = cn, cd = t[cn].len();
				else
					ns = mid, cn = t[cn](S[si][g]), cd = j-g;
			}
		}
	}
}
};
using sf::t;
int n;

int dfs(int u, int sz) {
	oc[u] = 0;
	if(t[u].adj.empty()) {
		oc[u] = n - (sz - 1);
		return oc[u];
	}
	for(auto e : t[u].adj)
		oc[u] = max(oc[u], dfs(e.second, sz + t[e.second].len()));
	return oc[u];
}


int memo[4123];
char s[212345];
int solve(int i) {
	if(i == n) return 0;
	int &r = memo[i];
	if(r != -1) return r;
	r = solve(i + 1) + 1;
	int cn = 0, cd = 0;
	for(int j = i; j < n; j++) {
		if(cd == t[cn].len())
			cn = t[cn](s[j]), cd = 0;
		cd++;
		if(oc[cn] > j) r = min(r, solve(j + 1) + 1);
	}
	return r;
}

void build(int i) {
	if(i == n) return;
	if(solve(i) == 1 + solve(i + 1)) {
		build(i + 1);
		printf("1 %c\n", s[i]);
		return;
	} 
	int cn = 0, cd = 0;
	for(int j = i; j < n; j++) {
		if(cd == t[cn].len())
			cn = t[cn](s[j]), cd = 0;
		cd++;
		if(oc[cn] > j && solve(i) == solve(j + 1) + 1) {
			build(j + 1);
			printf("2 %d %d\n", oc[cn] - (j + 1) + 1, oc[cn] - (j + 1) + 1 + (j - i));
			return;
		}
	}
}


int main () {
	while(true) {
		fgets(s, 21345, stdin);
		if(feof(stdin)) return 0;
		s[strlen(s) - 1] = 0;
		n = strlen(s);
		sf::add_string(s);
		dfs(0, 0);
		memset(memo, -1, sizeof memo);
		printf("Typing this string will require %d operations\n", solve(0));
		printf("These operations are the following:\n");
		build(0);
		sf::si = -1;
		for(int i = 0; i <= sf::en; i++)
			t[i] = sf::node();
		sf::sufn[0].clear();
		sf::en = 1;
		sf::lst = sf::ns = 0;
	}
}
