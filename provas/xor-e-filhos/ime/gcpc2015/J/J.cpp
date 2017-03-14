#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 102;

int memo[N][N][(N*N)/2];
int p[N], s[N], t[N];
int n, g, c;
char aux[N];

int f(int pr, int sr, int tr) {
    if (tr == 0) return pr * ((g-sr+pr-1)/pr);    
    else if (tr == 1) return pr * ((g-sr)/pr);
    else return pr * int( double(g-sr)/double(pr) + .5);
}

int dp(int i, int gc, int sc) {
    if(gc < 0 || sc < 0) return -1;
    if (i == n) return 0;
    int &me = memo[i][gc][sc];
    if(me != -1) return me;
    if(t[i] == 0) { //generous
        if(sc >= s[i]) me = max (1 + dp(i+1, gc, sc-s[i]),dp(i+1,gc,sc));    
        else me = max(1+dp(i+1,gc-1,sc+f(p[i],s[i],t[i])),dp(i+1,gc,sc));
    } else {
        me = max (1 + dp(i+1,gc-1, sc + f(p[i],s[i],t[i])), 1 + dp(i+1,gc,sc-s[i]));    
        me = max (me, dp(i+1,gc,sc));
    }
    return me;
}

int main () {
    scanf("%d %d %d",&g,&c,&n);
    memset(memo,-1,sizeof memo);
    for(int i = 0; i < n; i++) {
        scanf(" %s %d %d",aux,p+i,s+i); 
        if(strcmp(aux,"generous") == 0) t[i] = 0;
        else if(strcmp(aux,"greedy") == 0) t[i] = 1;
        else t[i] = 2;
    }
    printf("%d\n",dp(0,c,0));
}

