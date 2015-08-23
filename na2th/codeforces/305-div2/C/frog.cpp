#include<cstdio>
using namespace std;
typedef int num;
    num m, h1, a1, x1, y1,
    h2, a2, x2, y2, m1, m2, t1, t2;

int findCycle(num x0, num a, num b, num mod, int& s)
{
    num turtle = (1ull*x0*a + b)%mod,
        hare   = (1ull*a*a*x0 + a*b + b)%mod;
    int t;
    while( turtle != hare )
    {
        turtle = (1ull*a*turtle + b)%mod;
        hare   = (1ull*a*a*hare + a*b + b)%mod;
    }
    turtle = x0; s = 0;
    while( turtle != hare )
    {
        turtle = (1ull*turtle*a+b)%mod;
        hare   = (1ull*hare*a+b)%mod;
        s++;
    }
    hare = (1ull*turtle*a+b)%mod;
    t=1;
    while( turtle != hare )
    {
        hare = (1ull*hare*a+b)%mod;
        t++;
    }
    return t;
}

int main()
{
    scanf("%d", &m);
    scanf("%d %d", &h1, &a1);
    scanf("%d %d", &x1, &y1);
    scanf("%d %d", &h2, &a2);
    scanf("%d %d", &x2, &y2);
    t1 = findCycle(h1,x1,y1,m, m1);
    t2 = findCycle(h2,x2,y2,m, m2);
    for( m1 = 0; m1 < t1 && a1 != h1; m1++ )
        h1 = (1ull*x1*h1+y1);
    for( m2 = 0; m2 < t2 && a2 != h2; m2++ )
        h2 = (1ull*x2*h2+y2);
    printf("t1 = %d, m1 = %d\n", t1, m1);
    printf("t2 = %d, m2 = %d\n", t2, m2);
}
