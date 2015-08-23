#include<cstdio>
#include<set>
using namespace std;
typedef int num;
num h1,h2,x1,y1,x2,y2,a1,a2,m, t1, t2;
num f1,f2, aux1, aux2, p1, p2, ans1, ans2, ans;
num bd;
set<num> hf, hp;

num gcd( num a, num& ac, num b , num& bc)
{
    num d, ib, iab;
    if( b == 0 )
    {
        bc = 0; ac = 0; return a;
    }
    if( a%b == 0 )
    {
        ac = 0;
        bc = 1;
        return b;
    }
    d = gcd(b,ib,a%b, iab);
    ac = iab;
    bc = ib - (a/b)*iab;
    return d;
}

int main()
{
    scanf("%d", &m);
    scanf("%d %d", &h1, &a1);
    scanf("%d %d", &x1, &y1);
    scanf("%d %d", &h2, &a2);
    scanf("%d %d", &x2, &y2);
    f1 = aux1 = h1;
    hf.insert(f1);
    t1 = 0;
    for( int i = 0; i < m; i++ )
    {
        f1 = (1ull*x1*f1 + y1)%m;
        if( hf.count(f1) == 0 )
        {
            hf.insert(f1);
            t1++;
        }
        else
            break;
    }
    for( int i = 0; aux1 != f1 && i < m; i++ )
    {
        aux1 = (1ull*x1*aux1+y1)%m;
        t1--;
    }
    t1++;
    f2 = aux2 = h2;
    hp.insert(f2);
    t2 = 0;
    for( int i = 0; i < m; i++ )
    {
        f2 = (1ull*x2*f2 + y2)%m;
        if( hp.count(f2) == 0 )
        {
            hp.insert(f2);
            t2++;
        }
        else
            break;
    }
    for( int i = 0; aux2 != f2 && i < m; i++ )
    {
        aux2 = (1ull*x2*aux2+y2)%m;
        t2--;
    }
    t2++;
    if( hf.count(a1) == 0 || hp.count(a2) == 0 )
    {
        printf("%d\n", -1);
        return 0;
    }
    for( ; h1 != a1; h1 = (1ull*x1*h1+y1)%m ) p1++;
    for( ; h2 != a2; h2 = (1ull*x2*h2+y2)%m ) p2++;

    bd = gcd(t1, ans1, t2, ans2);
    printf("%d*%d + %d*%d = %d\n", t1,ans1,t2,ans2, bd);
    printf("%d*%d + %d = %d*%d +%d\n",p1,t1,ans1, p2,t2,ans2);
    ans = (ans1 > 0 ) ? (p1+t1*ans1)%t1 : (p2+t2*ans2)%t2 ;
    printf("%d\n", ans);

}
