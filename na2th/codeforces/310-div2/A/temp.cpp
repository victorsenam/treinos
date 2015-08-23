#include <bits/stdc++.h>
using namespace std;
typedef int num;
num n;
const int MS = 200001;
num st[MS], ss, ans;
char in[MS];

int main()
{
    scanf("%d", &n);
    scanf("%s", in);
    st[ss++] = 0;
    ans = n;
    for( int i = 1; i < n; i++ )
    {
        if( ss > 0 && in[i] != in[st[ss-1]] )
        {
            ans-=2;
            ss--;
        }
        else
            st[ss++] = i;
    }
    printf("%d\n", ans);
}
