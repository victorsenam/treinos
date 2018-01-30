#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
#define pb push_back
#define ws hajad
#define ref adsads

const int N = 1e7;

int n;
map<string,int> words[N];
map<char,int> letters[N];
int ws, ls, wc[N], lc[N], wl[N], ll[N], ref[N], wi[N], wj[N];
char text[5000];
vector<int> wr;

void add (int u, string s) {
	int & v = words[u][s];
	if (v) v = ++ws;
	wc[v]++; wl[v] = wl[u] + s.size();
}

void add (int u, char c) {
	int & v = letters[u][c];
	if (v) v = ++ls;
	lc[v]++; ll[v] = ll[u] + 1;
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("kina.in", "r", stdin);
	freopen("kina.out", "w", stdout);
#endif
	
	fread(text, 1, 5000, stdin);
	
	n = 0;
	bool inw = 0;
	for (int i = 0; text[i]; i++) {
		if (isalpha(text[i])) {
			if (!inw) wr.pb(n);
			inw = 1;
			text[n++] = tolower(text[i]);
		} else {
			if (inw) text[n++] = 0;
			inw = 0;
		}
	}

	ws = ls = 1;
	for (int i = 0; i < wr.size(); i++) {
		int w = 1, l = 1;
		for (int j = i; j < wr.size(); j++) {
			add(w,text+wr[j]);
			add(l,text[wr[j]]);
			wi[w] = i; wj[w] = j;
			ref[w] = l;
		}
	}

	int best = 0;
	int cur = 0;
	for (int u = 2; u <= ws; u++) {
		int loc = (wc[u]-1)*(wl[u]-ll[ref[u]]) - ll[ref[u]];
		if (wc[u] != lc[ref[u]]) continue;
		if (loc > best) {
			best = loc;
			cur = u;
		}
	}

	printf("%d\n", best);
	for (int i = wi[cur]; i <= wj[cur]; i++)
		putchar(text[wr[i]]);
	putchar('\n');
}
