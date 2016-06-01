#include <bits/stdc++.h>
using namespace std;
typedef int64_t ll;
const int N = 1e5 + 7;
const int T = (N<<1);

int n, q;
int tree[T];

int sgn(int x) { return (x>0) - (x<0); }
void update(int p, int x){
    for(tree[p+=n]=x;p;p>>=1) tree[p>>1] = sgn(tree[p]*tree[p^1]);
}
int query(int l, int r){
    int ans = 1;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1){
        if(l&1) ans *= tree[l++];
        if(r&1) ans *= tree[--r];
    }
    return ans;
}

int main(){
    while(scanf(" %d%d", &n, &q) != EOF){
        for(int i=n;i<2*n;i++) scanf(" %d", tree+i), tree[i] = sgn(tree[i]);
        for(int i=n-1;i>0;i--) tree[i] = tree[i<<1]*tree[i<<1|1];
        while(q--){
            char op; int i, j;
            scanf(" %c%d%d", &op, &i, &j); --i;
            if(op == 'C') update(i,sgn(j));
            else {
                int ans = query(i,j);
                if(ans == -1) putchar('-');
                else if(ans)  putchar('+');
                else          putchar('0');
            }
        }
        putchar('\n');
    }
}

