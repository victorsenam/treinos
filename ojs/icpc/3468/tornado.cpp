#include <bits/stdc++.h>
#define MAX 5005

using namespace std;
int N, X[MAX];

int main()
{
    N = 42;
    while( scanf("%d", &N) > 0 && N  )
    {
        for(int i = 0; i < N; i++)
            scanf("%d", X+i);

        int ans = 0,
            st = 0,
            gap, i;

        while( !X[st] && st < N ) st++; // Garante começar em 1

        if( st == N )
            printf("%d\n", N/2 + N%2);
        else
        {
            i = st + 1;
            while( i != st )
            {
                gap = 0;
                while( !X[i] && i != st )
                {
                    gap++;
                    i = (i+1)%N;
                }
                ans += gap/2;
                while( X[i] && i != st )
                    i = (i+1)%N;
            }
            printf("%d\n", ans);
        }
    }
}
