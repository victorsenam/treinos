#include <bits/stdc++.h>

using namespace std;

#define N 100

vector<int> g[N];
queue<int> q;
int v[N];
int n, e, a, b;
vector<int>::iterator it;

int dfs (int o, int i) {
    int res;

//    printf("%d, %d\n", o+1, i+1);
    if (v[i]) {
        v[i] = 2;
        return 1;
    } else {
        v[i] = 1;
    }

    for (vector<int>::iterator jt = g[i].begin(); jt != g[i].end(); jt++) {
        if (*jt == o) continue;
        res = dfs(i, *jt);
        if (res == 1) {
            if (v[i] == 2) return 2;
            else {
                v[i] = 2;
                return 1;
            }
        } if (res == 2) return 2;
    }
    return 0;
}

int main () {
    scanf("%d %d", &n, &e);

    for (int i = 0; i < n; i++) v[i] = 0;
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &a, &b);
        
        g[--a].push_back(--b);
        g[b].push_back(a);
    }

/* 
    for (int i = 0; i < n; i++) {
        printf("%d : ", i+1);
        for (vector<int>::iterator it = g[i].begin(); it != g[i].end(); it++) {
            printf("%d ", *it+1);
        }
        printf("\n");
    }
*/

    dfs(0, 0);

    for (int i = 0; i < n; i++) {
        if (v[i] == 2) {
            q.push(i);
            v[i] = -2;
        } else v[i] = -1;
    }

    while (!q.empty()) {
        a = q.front();
        q.pop();

        b = 0;

//        printf("%d : ", a+1);

        for (it = g[a].begin(); it != g[a].end(); it++) {
  //          printf("%d[%d] ", *it+1, v[*it]);
            if (v[*it] == -2) {
                if (++b > 2) {
    //                printf("Double Cycle");
                    break;
                } else {
                    continue;
                }
            } else if (v[*it] >= 0) {
                if (v[a] != *it) {
      //              printf("Cycle");
                    break;
                } else {
                    continue;
                }
            }
            
            v[*it] = a;
            q.push(*it);
        }
 //       printf("\n");

        if (it != g[a].end()) {
            printf("NO\n");
            return 0;
        }
    }

    for (a = 0; a < n && v[a] != -1; a++);
    
    if (a < n) printf("NO\n");
    else printf("FHTAGN!\n");
}
