#include<bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

const int S = 2e5;
char a[S], in[S];
num sol, ans[S];
vector<int> occ[2];
int m, n;

int main()
{
    scanf(" %s", a);
    n = strlen(a);
    scanf(" %s", in);
    m = strlen(in);
    for(int i=0;i<m;i++)
        occ[in[i]-'0'].push_back(i);

    for(int i=0;i+n<m+1;i++)
        ans[i] = n;

    for(int i=0;i+n<m;i++)
        sol += ans[i];
    cout << sol << endl;
}
