#include <bits/stdc++.h>
/*
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <map>
*/
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define fst first
#define scd second
#define f(x, let) for(int let=0; let<x; let++)
#define ms(x, v) memset(x, v, sizeof x)
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pair<int, int> > vpi;
typedef set<int> si;
typedef set<int>::iterator sit;
const int MOD = 1000000007;
const int OO = 0x3f3f3f;
//REMEMBER LONG LONG INT
//REMEMBER TO INITIALZE THINGS

int mat[1007][1007];
int vpd[1007][1007];
int is[] = {1, -1, 0, 0};
int js[] = {0, 0, 1, -1};
int n, m, k;

int main(){
    std::ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    ms(vpd, 0);
    f(n, i){
        f(m, j){
            char c;
            cin >> c;
            if(c=='.') mat[i][j] = 1;
            else mat[i][j] = 0;
        }
    }
    queue<pi> q;
    stack<pi> s;
    f(k, i){
        int a, b;
        cin >> a >> b;
        if(!vpd[a-1][b-1]){
            int tot = 0;
            q.push(mp(a-1, b-1));
            vpd[a-1][b-1] = 1;
            while(!q.empty()){
                pi c = q.front();
                q.pop();
                s.push(c);
                f(4, i){
                    if(c.fst+is[i] < 0 || c.fst+is[i]>=n || c.scd+js[i] < 0 || c.scd+js[i]>=m) continue;
                    if(mat[c.fst+is[i]][c.scd+js[i]] && !vpd[c.fst+is[i]][c.scd+js[i]]){
                        q.push(mp(c.fst+is[i], c.scd+js[i]));
                        vpd[c.fst+is[i]][c.scd+js[i]] = 1;
                    }
                    else if(!mat[c.fst+is[i]][c.scd+js[i]]) tot++;
                }
            }
            while(!s.empty()){
                pi c = s.top();
                s.pop();
                vpd[c.fst][c.scd] = tot;
            }
        }
        cout << vpd[a-1][b-1] << "\n";
    }
}
