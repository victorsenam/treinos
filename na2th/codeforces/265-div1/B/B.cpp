#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long num;

const int N = 8;
num in[N][3], cnt;
int p[N], anc;

inline num dist(int i, int j)
{
    num ans = 0;
    for(int k=0;k<3;k++)
        ans += (in[i][k]-in[j][k])*(in[i][k]-in[j][k]);
    return ans;
}
bool distLess(int i, int j)
{ return mp(dist(p[0],i), i) < mp(dist(p[0],j), j); }

bool solve(int i)
{
    if(i == 8) 
    {
        sort(p+1,p+8, distLess);
        num d = dist(p[0], p[1]);
        int ok = 1;
        for(int i=0;i<8;i++)
            for(int j=i+1;j<8;j++)
                ok &= (in[i][0] != in[j][0] ||
                       in[i][1] != in[j][1] ||
                       in[i][2] != in[j][2]   );
        for(int i=1;i<4;i++)
            ok &= (d == dist(p[0],p[i]));
        for(int i=4;i<7;i++)
            ok &= (2*d == dist(p[0],p[i]));
        ok &= (3*d == dist(p[0],p[7]));
        return ok;
    }
    do
    {
        if(solve(i+1)) return true;
    } while(next_permutation(in[i], in[i]+3));
    return false;
}

int main()
{
    for(int i=0;i<8;i++) p[i] = i;
    for(int i=0;i<N;i++)
        for(int j=0;j<3;j++)
            cin >> in[i][j];
    for(int i=0;i<N;i++)
        sort(in[i], in[i]+3);
    if(solve(0))
    {
        printf("YES\n");
        for(int i=0;i<8;i++,putchar('\n'))
            for(int j=0;j<3;j++)
                cout << in[i][j] << ' ';
    }
    else
        printf("NO\n");
}
