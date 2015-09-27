#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = 4002;
char s[MS], u[MS];
int ns, nu, fix, sol[MS];
set<int> seen[30];
set<int>::iterator it;

int main ()
{
    scanf(" %s", s); ns = strlen(s);
    scanf(" %s", u); nu = strlen(u);
    fix = max(nu, ns);
    for (int i=0;i<ns;i++)
        seen[s[i]-'a'].insert(i);

    for (int i=0;i<MS;i++)
        sol[i] = nu;

    for (int i=0;i<nu;i++)
        for(it = seen[u[i]-'a'].begin(); it != seen[u[i]-'a'].end(); ++it)
            sol[fix+*it-i]--;

    printf("%d\n", *min_element(sol, sol+MS));
}
