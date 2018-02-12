#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e2+3;
const int M = 4e4+4;

char chrs[N];
string chrss;
vector<char> memo[M][N];
char s[N];
bool bad[M];
map<char,int> fst[M];
map<char,int> tr[M];
int en = 1;
int F[M];
int n, m, p;

vector<char> soma (vector<char> & a, vector<char> b) {
	vector<char> res;
	char carry = 0;
	int i = 0;
	for (i = 0; i < a.size() && i < b.size(); i++) {
		res.pb(a[i] + b[i] + carry);
		carry = res[i]/10;
		res[i] %= 10;
	}
	while (i < a.size()) {
		res.pb(a[i] + carry); 
		carry = res[i]/10;
		res[i] %= 10;
		i++;
	}
	while (i < b.size()) {
		res.pb(b[i] + carry); 
		carry = res[i]/10;
		res[i] %= 10;
		i++;
	}
	while (carry) {
		res.pb(carry); 
		carry = res[i]/10;
		res[i] %= 10;
		i++;
	}
	return res;
}

vector<char> pd (int u, int m) {
	vector<char> & me = memo[u][m];
	if (me.size()) return me;

	if (bad[u]) return vector<char>({0});
	if (m == 0) return vector<char>({1});

	me = vector<char>(0);
	for (char c : chrss)
		me = soma(me, pd(fst[u][c],m-1));
	return me;
}

int main () {
	scanf("%d %d %d", &n, &m, &p);
	scanf("%s", chrs);
	chrss = chrs;
	for(int i = 0; i < p; i++) {
		scanf("%s", s);
		int v = 0;
		for(int j = 0; s[j]; j++) {
			if(!tr[v].count(s[j]))
				tr[v][s[j]] = en++;
			v = tr[v][s[j]];
		}
		bad[v] = 1;
	}
	queue<int> q;
	for(auto e : tr[0])
		q.push(e.second), F[e.second] = 0;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		for(auto e : tr[x]) {
			int y = e.second;
			F[y] = F[x];
			while(F[y] && !tr[F[y]].count(e.first))
				F[y] = F[F[y]];
			if(tr[F[y]].count(e.first))
				F[y] = tr[F[y]][e.first];
			if(bad[F[y]]) bad[y] = true;
			q.push(y);
		}
	}
	for(int y = 0; y < en; y++) {
		for(char c : chrss) {
			fst[y][c] = y;
			while(fst[y][c] && !tr[fst[y][c]].count(c))
				fst[y][c] = F[fst[y][c]];
			if(tr[fst[y][c]].count(c))
				fst[y][c] = tr[fst[y][c]][c];
		}
	}
	vector<char> r = pd(0,m);
	reverse(r.begin(), r.end());
	for (char c : r)
		putchar(c+'0');
	putchar('\n');
}
