#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

int n, m;
int ind[N];
bool ty[N];
int cul[N];
int def[N];
int qtds[N];
int tc, ti;
int pc[N], pi[N];
char c;
int culps;

void res(int a){ 
    if (a == 0)
        printf("Lie\n");
    else if (a == 1)
        printf("Truth\n");
    else
        printf("Not defined\n");
}

int main () {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf(" %c%d", &c, ind+i);
        ind[i]--;
        ty[i] = (c=='+');
        if (ty[i]) {
            cul[ind[i]]++;
            tc++;
        } else {
            def[ind[i]]++;
            ti++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (ti - def[i] + cul[i] == m) {
            pc[i] = 1;
            culps++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (ty[i]) {
            if (pc[ind[i]])
                res(2 - (culps == 1));
            else
                res(0);
        } else {
            if (pc[ind[i]]) {
                res(-1 + (culps == 1));
            } else {
                res(1);
            }
        }
    }
}
