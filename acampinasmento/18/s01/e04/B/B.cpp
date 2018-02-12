#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int mat[100][100];
// 0 unseen
// 1 empty
// 2 blocked


int di[] = {-1, 0, 1, 0, -1};
int dj[] = {-1, 1, 0, -1, 0};

int seen[100][100], tempo;

deque<int> path;

int dfs(int i, int j) {
	if(mat[i][j] == 0) {
		//printf("going to %d, %d\n", i - 50, j - 50);
		return 1;
	}
	if(mat[i][j] == 2) return 0;
	if(seen[i][j] == tempo) return 0;
	seen[i][j] = tempo;
	for(int d = 1; d <= 4; d++) {
		int ni = i + di[d], nj = j + dj[d];
		path.pb(d);
		if(dfs(ni, nj)) return d;
		path.pop_back();
	}
	return 0;
}

int i, j;

char tmp[100];
string str[] = {"", "EAST", "SOUTH", "WEST", "NORTH"};

int main () {
	i = j = 50;
	mat[i][j] = 1;
	tempo++;
	while(true) {
		if(path.empty() && !dfs(i, j)) break;
		//for(int x : path) printf("%s ", str[x]); putchar('\n');
		int d = path.front(); path.pop_front();
		puts(str[d].c_str());
		fflush(stdout);
		scanf("%s", tmp);
		int ni = i + di[d], nj = j + dj[d];
		if(tmp[0] == 'B') {
			mat[ni][nj] = 2;
		} else {
			i = ni;
			j = nj;
			mat[i][j] = 1;
		}
		tempo++;
	}
	puts("DONE");
}
