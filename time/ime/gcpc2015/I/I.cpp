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

const int N = (1e4)+7;

int w,st,x,y,aux;
int in[N][200], s[N];

int main () {
    scanf(" %d%d", &w, &st);
    scanf(" %d%d", &x, &y);
    for(int i=0;i<w;i++){
        for(int j=0;j<x;j++)
            scanf(" %d", &in[i][j]);
    }
    while(st--){
        for(int i=0;i<x;i++){
            scanf(" %d", &aux);
            s[i] = max(s[i], aux);
        }
    }
    for(int i=0;i<w;i++)
        for(int j=0;j<x;j++)
            printf("%d%c", min(in[i][j], y-s[j])," \n"[j+1==x]);
}
