#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef long double cood;
typedef complex<cood> point;

const int N = 1e5;
const cood PI = acos(-1.0);
int n, bi, p[N];
point P[N], O;
cood ix, iy, best, guess;

bool argLess(int i, int j)
{ return arg(P[i]) < arg(P[j]); }

cood angle(point a, point b, point c)
{  return abs(remainder(arg(a-c)-arg(b-c), 2.*PI)); }

int main()
{
    O = point(0,0);
    cin >> n;
    for(int i=0;i<n;i++)
    {
        cin >> ix >> iy;
        P[i] = point(ix, iy);
        p[i] = i;
    }
    sort(p, p+n, argLess);
    best = angle(P[p[0]], P[p[1]], O);
    bi = 0;
    for(int i=0;i<n;i++)
    {
        int j = (i+1)%n;
        if((guess=angle(P[p[i]],P[p[j]],O)) < best)
        {
            best = guess;
            bi = i;
        }
    }
    cout << p[bi]+1 << " " <<  p[(bi+1)%n]+1 << endl;
}
