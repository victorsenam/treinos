#include<bits/stdc++.h>
#define MAX 5000
using namespace std;
typedef int num;
num a[MAX], b[MAX], p[MAX],n, ans;

int main()
{
    cin >> n;
    for(int i=0;i<n;i++)
    {
        cin >> a[i] >> b[i];
        p[i] = i;
    }
    sort(p,p+n,[&](int a0, int a1)
    { return a[a0] < a[a1];});
    for(int i=0;i<n;i++)
        cout << a[p[i]] << " " << b[p[i]] << endl;
}
