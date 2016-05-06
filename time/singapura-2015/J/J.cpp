#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000000;
const int T = (N<<1) + 7;
const int S = 150;
typedef bitset<S> node;

node tree[T];
int ad[N], ini[N], fim[N], curr[N], tmp;
int to[N], nx[N], es;
int n, q;

void update(int p){
	for(p+=n;p;p>>=1)
		tree[p>>1] = (tree[p]^tree[p^1]);
}
node query(int l, int r){
	node ans; ans.reset();
	for(l+=n,r+=n;l<r;l>>=1,r>>=1){
		if(l&1) ans = (ans^tree[l++]);
		if(r&1) ans = (ans^tree[--r]);
	}
	return ans;
}
void dfs(int u){
	ini[u] = tmp++;
	for(int e=ad[u];e;e=nx[e]) dfs(to[e]);
	fim[u] = tmp;
}
int main(){
	while(scanf(" %d%d", &n, &q) != EOF) {
		memset(ad, 0, sizeof ad); es = 1;
		for(int i=0;i<n;i++) scanf(" %d", curr+i);
		for(int i=1;i<n;i++){
			int j; scanf(" %d", &j); --j;
			to[es] = i; nx[es] = ad[j]; ad[j] = es++;
		}
		tmp = 0; dfs(0);
		for(int i=0;i<n;i++) {
			tree[ini[i]+n].reset();
			tree[ini[i]+n].set(curr[i]);
		}
		for(int i=n-1;i>0;--i) tree[i] = (tree[i<<1]^tree[(i<<1)|1]);
		while(q--){
			int k, x;
			scanf(" %d%d", &k, &x); --x;
			if(k == 0) printf("%lu\n", query(ini[x],fim[x]).count());
			else {
				int i = ini[x];
				tree[i+n].reset(); tree[i+n].set(k);
				update(i);
			}
		}
	}
}
