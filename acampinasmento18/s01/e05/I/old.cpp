#include <bits/stdc++.h>
//#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct node {
	map<char, node*> f;

	node * fail;
	int L;
	node (int a) : fail(NULL), L(a) {}
};

node *root;
node *last;
inline void step(char c) {
	static int sz = 0;
	node *p = last;
	last = new node(++sz);
	while (p != NULL && p->f.count(c) == 0) {
		p->f[c] = last;
		p = p->fail;
	}
	if (p == NULL)
		last->fail = root;
	else {
		node *y = p->f[c];
		if (y->L == p->L + 1)
			last->fail = y;
		else {
			node *x = new node(p->L + 1);
			x->f = y->f;
			x->fail = y->fail;
			y->fail = last->fail = x;
			while(p != NULL && p->f.count(c) != 0 && p->f[c] == y) {
				p->f[c] = x;
				p = p->fail;
			}
		}
	}
}

void start() {
	root = new node(0);
	last = root;
}

void add(string &s) {
	for(char c : s)
		step(c);
}

bool test(string &s) {
	node *x = root;
	for(char c : s) {
		if(!x->f.count(c)) return false;
		x = x->f[c];
	}
	return true;
}

string str;
char ss[212345];

int main () {
	char q;
	start();
	while (scanf(" %c", &q) != EOF) {
		scanf("%s", ss);
		str =ss;
		for(char &c : str) c = tolower(c);
		if (q == '?') {
			printf("%s\n", test(str)?"YES":"NO");
		} else {
			add(str);
		}
	}

}
