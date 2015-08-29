#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = 10;
char in[MS]; int n;

double solve(int p, num state, num goal)
{
    double ans=0.0;
    if( p == n ) return ( state == goal );
    if( in[p] == '?' )
        ans = 0.5*( solve(p+1,state+1,goal) + solve(p+1,state-1, goal) );
    else if( in[p] == '+' )
        ans = solve(p+1, state+1, goal);
    else if( in[p] == '-' )
        ans = solve(p+1, state-1, goal);
    return ans;
}

int main()
{
    cin >> in;
    int goal = 0;

    for(n=0;in[n]!=0;n++)
        if(in[n] == '+')
            goal++;
        else
            goal--;
    cin >> in;
    cout <<  setiosflags(ios::fixed) << setprecision(9) << solve(0, 0, goal) << "\n";
}
