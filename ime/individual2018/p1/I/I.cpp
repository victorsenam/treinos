#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 50+7;

vector<int> adj[2][N];
char * str[3];
int dist[N][N];
int visi[N][N];

void process (int k) {
	stack<int> st;
	int i;
	for (i = 0; str[k][i] != '\n'; i++) {
		adj[k][i].clear();
		adj[k][i].pb(i);
		if (str[k][i] == '(') { st.push(i); adj[k][i].pb(i+1); }
		else if (str[k][i] == '|') { adj[k][st.top()].pb(i+1); st.push(i); }
		else if (str[k][i] == '*') { adj[k][st.top()].pb(i); adj[k][i].pb(st.top()); adj[k][i].pb(i+1); }
		else if (str[k][i] == ')') {
			adj[k][i].pb(i+1);
			if (str[k][st.top()] == '|') {
				adj[k][st.top()].pb(i);
				st.pop();
			}
			st.pop();
		}
	}
	adj[k][i].clear();
	adj[k][i].pb(i);
}

bool isL (char a) {
	return a == 'a' || a == 'b';
}

int main () {
	int ts;
	scanf("%d",&ts);
	for (int k = 0; k < 2; k++)
		str[k] = (char *) malloc(sizeof(char)*N);
	while (ts--) {
		for (int k = 0; k < 3; k++) {
			unsigned long int n = N;
			getline(&str[k-!!k], &n, stdin);
			process(k-!!k);
		}

		memset(dist, 0x3F3F3F, sizeof dist);
		deque<pii> qu;
		qu.push_back(pii(0,0));
		dist[0][0] = 0;

		int res = -1;
		
		while (!qu.empty()) {
			pii c = qu.front();
			qu.pop_front();
			int a = c.first, b = c.second;

			if (str[0][a] == '\n' && str[1][b] == '\n') { res = dist[a][b]; break; }

			//cout << a << str[0][a] << " " << b << str[1][b] << ": " << dist[a][b] << endl;

			if (dist[a][b] == -1) continue;
			
			for (int na : adj[0][a]) {
				for (int nb : adj[1][b]) if (dist[na][nb] > dist[a][b]) {
					dist[na][nb] = dist[a][b];
					qu.push_front(pii(na,nb));
				}
			}
			if (isL(str[0][a]) && isL(str[1][b])) {
				if (str[0][a] == str[1][b]) {
					if (dist[a+1][b+1] > dist[a][b]) {
						dist[a+1][b+1] = dist[a][b];
						qu.push_front(pii(a+1,b+1));
					}
				} else {
					if (dist[a+1][b+1] > dist[a][b] + 1) {
						dist[a+1][b+1] = dist[a][b] + 1;
						qu.push_back(pii(a+1,b+1));
					}
				}
			}
			if (isL(str[0][a]) && dist[a+1][b] > dist[a][b] + 1) {
				dist[a+1][b] = dist[a][b] + 1;
				qu.push_back(pii(a+1,b));
			}
			if (isL(str[1][b]) && dist[a][b+1] > dist[a][b] + 1) {
				dist[a][b+1] = dist[a][b] + 1;
				qu.push_back(pii(a,b+1));
			}
			dist[a][b] = -1;
		}

		printf("%d\n", res);
	}
	for (int k = 0; k < 2; k++)
		free(str[k]);
}
