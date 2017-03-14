#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

vector<int> fact[N];
set<int> used[N];
bool on[N];
int n, m;
int a;
char o;

int main () {
    for (int i = 2; i < N; i++) {
        if (fact[i].size())
            continue;

        for (int j = 1; i*j < N; j++) {
            fact[i*j].push_back(i);
        }
    }

    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf(" %c %d", &o, &a);
        
        if (o == '+') {
            if (on[a])
               printf("Already on\n");
            else {
                int i = 0;
                for (i = 0; i < fact[a].size(); i++) {
                    if (used[fact[a][i]].size()) {
                        printf("Conflict with %d\n", *(used[fact[a][i]].begin()));
                        break;
                    }
                }

                if (i == fact[a].size()) {
                    on[a] = 1;
                    for (i = 0; i < fact[a].size(); i++)
                        used[fact[a][i]].insert(a);
                    printf("Success\n");
                }
            }
        } else {
            if (!on[a])
                printf("Already off\n");
            else {
                for (int i = 0; i < fact[a].size(); i++)
                    used[fact[a][i]].erase(a);
                on[a] = 0;
                printf("Success\n");
            }
        }
    }
}
