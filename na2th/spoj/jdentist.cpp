#include<bits/stdc++.h>
#define MAX 100003
using namespace std;
typedef int num;
num n, ini[MAX], fim[MAX];

num maximize( int curr, int minT ) 
{
    int next = curr;
    while( ini[curr] < minT ) curr++;
    if( curr >= n ) return 0;
    // Acho todos os conflitos
    while( next < n && ini[next] < fim[curr]) next++;
    // Escolho a que acaba mais cedo
    int best = -1, end = INT_MAX;
    for( int p = curr; p < next; p++ )
        if( fim[p] < end )
        {
            best = p;
            end  = fim[p];
        }

    return 1 + maximize(best+1, end);
}

int main()
{
    scanf("%d", &n);
    for( int i = 0; i < n; i++ )
        scanf("%d %d", ini+i, fim+i);
    printf("%d\n", maximize(0, INT_MIN));
}
