#include <bits/stdc++.h>
using namespace std;

const int N = 4e6;
const int T = (N<<1) + 7;
const int M = T;
const int S = 150;

int n, q;
int ad[N], ini[N], fim[N], tmp;
int to[M], nx[M], es;
int curr[T];
bitset<S> tree[T], zero;

void update(int t){
	while(t) {
		tree[t>>1] = (tree[t] ^ tree[t^1]);
		t >>= 1;
	}
}
bitset<S> query(int l, int r){
	bitset<S> ans; ans = zero;
	for(l+=n,r+=n;l<r;l>>=1,r>>=1){
		if(l&1) ans = (ans ^ tree[l++]);
		if(r&1) ans = (ans ^ tree[--r]);
	}
	return ans;
}
void dfs(int i){
	ini[i] = tmp++;
	for(int e=ad[i];e;e=nx[e]) dfs(to[e]);
	fim[i] = tmp;
}

int main(){
	for(int i=0;i<S;i++) zero.reset(i);
	while(scanf(" %d%d", &n, &q) != EOF){
		for(int i=0;i<n;i++) scanf(" %d", curr+i);
		for(int i=0;i<n;i++) ad[i] = 0, ini[i] = -1; es = 2;
		for(int i=0;i<n;i++) {
			tree[i+n] = zero;
			tree[i+n].set(curr[i]);
		}
		for(int i=n-1;i>0;--i) tree[i] = (tree[i<<1] ^ tree[(i<<1)|1]);
		for(int i=1;i<n;i++){
			int j;
			scanf(" %d", &j); --j;
			to[es] = i; nx[es] = ad[j]; ad[j] = es++;
		}
		tmp = 0;
		dfs(0);
		while(q--){
			int k, x; scanf(" %d%d", &k, &x); --x;
			if(k == 0) printf("%d\n", query(ini[x],fim[x]).count());
			else {
				int i = ini[x];
				tree[i+n] = zero;
				tree[i+n].set(k);
				update(i+n);
			}
		}
	}
}
