#include <bits/stdc++.h>
using namespace std;
typedef long long num;

inline int monthLen(int i)
{
    if(i == 1) return 28;
    if(i < 7) return 30 + !(i&1);
    i -= 8;
    return 30 + (i&1);
}

inline int leapYear(int y)
{
    if(!y%400) return 1;
    if(!y%100) return 0;
    return !(y%4);
}

int m, y, tot, week_day;
int main()
{
    tot = 0;
    week_day = (366)%7;
    for(y=1901;y<2001;y++)
        for(m=0;m<12;m++)
        {
            tot += (week_day == 0);
            week_day = (week_day + monthLen(m) + (m==1)*leapYear(y))%7;
        }
    printf("%d\n", tot);
}
