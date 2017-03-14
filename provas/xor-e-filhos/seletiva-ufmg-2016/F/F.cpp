#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5;
const int T = (N<<1);

int n, m, q;
int V[T][2], H[T][2], t, c;

void paint(int tree[T][2], int s, int l, int r) {
	for(l+=s,r+=s;l<r;l>>=1,r>>=1){
		if(l&1) {
			tree[l][0] = t;
			tree[l++][1] = c;
		}
		if(r&1) {
			tree[--r][0] = t;
			tree[r][1] = c;
		}
	}
}

void query(int tree[T][2], int s, int p) {
	t = tree[p+=s][0]; c = tree[p][1]; p>>=1;
	for(;p>0;p>>=1) if(tree[p][0] > t) t = tree[p][0], c = tree[p][1];
}

int main(){
	scanf(" %d%d%d", &n, &m, &q);
	for(int k=1;k<1+q;k++){
		char op; int i, j;
		scanf(" %c%d%d", &op, &i, &j);
		if(op == 'C') {
			query(V,m,--j);
			int _t = t, _c = c;
			query(H,n,--i);
			if(_t > t) swap(_c, c);
			printf("%d\n", c);
		} else {
			scanf(" %d", &c); t = k;
			if(op == 'H') paint(H, n, --i, j);
			else          paint(V, m, --i, j);
		}
	}
}
