#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct node {
	map<char, node*> f;

	node * fail;
	int L;
	bool mrk;
	int count;
	int id;
	int seen;
	node (int a) : fail(NULL), L(a), mrk(false), count(0), seen(0) {}
};

node* build_suffix_automaton(const string &P) {
	int count = P.size() + 1;
	node *root = new node(0);
	node *last = root;
	for (int i = 0; i < P.size(); i++) {
		node *p = last;
		last = new node(i+1);
		while (p != NULL && p->f.count(P[i]) == 0) {
			p->f[P[i]] = last;
			p = p->fail;
		}
		if (p == NULL)
			last->fail = root;
		else {
			node *y = p->f[P[i]];
			if (y->L == p->L + 1)
				last->fail = y;
			else {
				node *x = new node(p->L + 1);
				count++;
				x->f = y->f;
				x->fail = y->fail;
				y->fail = last->fail = x;
				while(p != NULL && p->f.count(P[i]) != 0 && p->f[P[i]] == y) {
					p->f[P[i]] = x;
					p = p->fail;
				}
			}
		}
	}
	node *p = last;
	while (p != NULL) {
		p->mrk = true;
		p = p->fail;
	}
	return root;
}

int n, m;

vector<int> fin;
int tempo = 1;
void dfs(node *n, bool prn) {
	if(n->seen == tempo) return;
	if(prn && n-> mrk) fin.pb(n->id);
	n->seen = tempo;
	if(!prn)
		n->id = ++::n;
	for(auto p : n->f) {
		m++;
		if(prn) {
			printf("%d %d %c\n", n->id, p.second->id, p.first);
		}
		dfs(p.second, prn);
	}

}

int main () {
	string s;
	cin >> s;
	node *r = build_suffix_automaton(s);
	dfs(r, false);
	printf("%d %d\n", n, m);
	tempo++;
	dfs(r, true);
	printf("%d\n", int(fin.size()));
	for(int x : fin) printf("%d ", x);
	putchar('\n');
}
