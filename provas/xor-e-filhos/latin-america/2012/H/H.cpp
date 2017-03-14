#include <bits/stdc++.h>
using namespace std;
typedef int64_t ll;

const int S = 1e6+7;
const int Z = 'z'-'A'+2;

double ans;
int n;
char in[200];

int _T[S*Z], *T[S], ts, tree;
char c[S];
int sol[S];
bool f[S];

int create(int t){
    f[t] = 0;
    for(char i='A';i<'A'+Z;i++) T[t][i] = 0;
    return t;
}

void insert(int t, char * s){
    if(*s == 0) return (void)(f[t] |= 1);
    if(T[t][*s] == 0) c[T[t][*s] = create(ts++)] = *s;
    insert(T[t][*s], 1+s);
}

void solve(int t, int partial){
    if(!t) return;
    int cnt = 0;
    for(char i='A';i<'A'+Z;i++) cnt += (!!T[t][i]);

    sol[t] = partial + (t == 1 || f[t] || (cnt > 1));
    if(f[t]) ans += sol[t];

    for(char i='A';i<'A'+Z;i++) solve(T[t][i], sol[t]);
}

int main(){
    for(int i=0;i<S;i++) T[i] = _T + i*Z - 'A';
    while(scanf(" %d", &n) != EOF){
        ts = 1;
        tree = create(ts++); c[tree] = '$';
        ans = 0;
        for(int i=0;i<n;i++) {
            scanf(" %s", in);
            insert(tree, in);
        }
        solve(tree, 0);
        printf("%.2lf\n", ans/n - 1.);
    }
}
