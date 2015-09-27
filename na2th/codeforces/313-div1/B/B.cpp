#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef long long hsh;
typedef int node;
typedef int edge;
const int MS = 200002;
int n, m;
char s1[MS], s2[MS];

int main()
{
    scanf(" %s %s", s1, s2);

    n = strlen(s1);
    for(m=n;m%2==0;m/=2);

    while( m < n )
    {
        for(int i=0;i<n/m;i+=2)
        {
            int k = 0;
            while(k<m && s1[i*m+k] == s1[(i+1)*m+k]) k++;
            if( k<m && s1[i*m+k] > s1[(i+1)*m+k] )
                for(int j=0;j<m;j++)
                    swap(s1[i*m+j],s1[(i+1)*m+j]);
            k = 0;
            while(k<m && s2[i*m+k] == s2[(i+1)*m+k]) k++;
            if(k<m && s2[i*m+k]>s2[(i+1)*m+k])
                for(int j=0;j<m;j++)
                    swap(s2[i*m+j],s2[(i+1)*m+j]);
        }
        m *= 2;
    }
    if(strcmp(s1,s2) == 0)
        printf("YES\n");
    else
        printf("NO\n");
}
