#include <cstdio>

using namespace std;

int main()
{
    int q, d, p, ans;
    while ( scanf("%d%d%d", &q, &d, &p) > 0 ) {
        if( q == 0 ) break;
        ans = d*p*q;
        ans /= ( p > q )? p-q : q-p;
        printf("%d paginas\n", ans);
    }
}
