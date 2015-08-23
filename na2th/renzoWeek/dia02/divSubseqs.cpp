#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int num;
const num MN = 50003;
num d, n, in[MN], ans, pos, cnt, curr;

int main()
{
    ios::sync_with_stdio(false);
    int tc;
    cin >> tc;
    while(tc--)
    {
        cin >> d >> n;
        in[0] = 0; n++;
        for(int i=1;i<n;i++)
        {
            cin >> in[i];
            in[i] = (in[i] + in[i-1])%d;
        }
        sort(in, in+n);
        ans = 0;
        pos = 0;
        while( pos < n )
        {
            curr = in[pos];
            cnt  = 0;
            while( pos < n && in[pos] == curr ){
                pos++;
                cnt++;
            }
            ans += (cnt*(cnt-1))/2;
        }

        cout << ans << "\n";
    }
}
