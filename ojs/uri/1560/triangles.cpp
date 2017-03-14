#include <bits/stdc++.h>
#define MAX 105

using namespace std;

typedef int num;
typedef pair<num, num> pt;

pt W[MAX], B[MAX];
int N, M;
long long ans;

num cP(pt A, pt B, pt C)
{
    // A.f A.s 1
    // B.f B.s 1
    // C.f C.s 1
    return A.first *(B.second - C.second)
         + A.second*(C.first - B.first)
         + B.first*C.second - B.second*C.first;
}

num sign( num a )
{
    if ( a > 0 ) return 1;
    else if ( a < 0 ) return -1;
    return 0;
}

int main()
{
    N = M = 42;
    while( scanf("%d %d", &N, &M) > 0 && N && M )
    {
        ans = 0;
        num x, y;
        for( int i = 0; i < N; i++ )
        {
            scanf("%d %d", &x, &y);
            B[i] = make_pair(x , y);
        }

        for( int i = 0; i < M; i++ )
        {
            scanf("%d %d", &x, &y);
            W[i] = make_pair(x , y);
        }

        // Cada tripla forma um triangulo
        for( int i = 0; i < N; i++ )
            for ( int j = i + 1; j < N; j++ )
                for ( int k = j + 1; k < N; k++ )
                {
                    num ori = sign( cP(B[i],B[j],B[k]) );
                    int in = 0;// Pontos dentro desse triangulo
                    for(int p = 0; p < M; p++)
                    {
                        if( sign(cP(B[i], B[j], W[p])) == ori &&
                            sign(cP(B[j], B[k], W[p])) == ori &&
                            sign(cP(B[k], B[i], W[p])) == ori )
                            in++;
                    }
                    ans += in*in;
                }
        printf("%lld\n", ans);
    }
}
