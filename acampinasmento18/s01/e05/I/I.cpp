#include <bits/stdc++.h>
//#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back


const int NS = 1;
const int N = 212345 * 2;

int cn, cd, ns, en = 1, lst;
string S[NS]; int si = -1;
vector<int> sufn[N];

struct node {
	int l, r, si;
	int p, suf;
	bool root = false;
	map<char, int> adj;
	node() : l(0), r(-1), suf(0), p(0) {}
	node(int L, int R, int S, int P) : l(L), r(R), si(S), p(P) {}
	inline int len() { if(root) return 0; return (r == -1? S[si].size() : r) - l + 1; }
	inline int operator[](int i) { return S[si][l+i]; }
	inline int& operator()(char c) { return adj[c]; }
} t[N];

inline int new_node(int L, int R, int S, int P) {
	t[en] = node(L,R,S,P);
	return en++;
}

int i;
inline void step(char c) {
	S[0].pb(c);
	int j = S[0].size() - 1;
	const string &s = S[0];
	for (; i <= j; i++) {
		if (cd == t[cn].len() && t[cn](s[j]))
			cn = t[cn](s[j]), cd = 0;
		if (cd < t[cn].len() && t[cn][cd] == s[j]) {
			cd++;
			if (j < s.size() - 1) break;
			else {
				if (i) t[lst].suf = cn;
				for(; i<=j;i++) {
					cn = t[cn].suf;
				}
			}
		} else if (cd == t[cn].len()) {
			if(i) t[lst].suf = en; lst=en;
			t[cn](s[j]) = new_node(j,-1,si,cn);
			cn = t[cn].suf;
			cd = t[cn].len();
		} else {
			int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].si, t[cn].p);
			t[t[cn].p](t[cn][0]) = mid;
			if(ns) t[ns].suf = mid;
			if(i) t[lst].suf = en; lst = en;
			t[mid](s[j]) = new_node(j,-1,si,mid);
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

void start() {
	++si;
	cn = cd = 0;
	i = 0;
	t[0].root = true;
}

void add(string &s) {
	for(char c : s)
		step(c);
}

bool test(string &s) {
	int cn = 0, cd = 0;
	for(char c : s) {
		if(cd == t[cn].len()) {
			if(!t[cn].adj.count(c)) {
				//printf("no1\n");
				return false;
			}
			cn = t[cn](c);
			cd = 0;
		}
		if(t[cn][cd] != c) {
			//printf("no %c vs %c\n", t[cn][cd], c);
			return false;
		}
		cd++;
	}
	return true;
}

string str;

char ss[112345];

int main () {
	char q;
	start();
	while (scanf(" %c", &q) != EOF) {
		scanf(" %s", ss);
		str = ss;
		for(char &c : str) c = tolower(c);
		if (q == '?') {
			printf("%s\n", test(str)?"YES":"NO");
		} else {
			add(str);
		}
	}

}
