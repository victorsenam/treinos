#include<bits/stdc++.h>
using namespace std;
typedef long long num;
const int MP = 250001;
const num FX = 10000;
const num MR = 2*FX;
const int MQ = 10001;
set< pair<num, num> > tree[2*MR], pre;
set< pair<num, num> >::iterator it, goal;
num x[22], y[22], wss;

int tc;
int s, w, p;
num r;

void query(num qx, num qy)
{
    num ly = max(qy-r+FX,0ll),
        ry = min(qy+r+FX,MR),
        lx = qx-r,
        rx = qx+r;
    for(ly+=MR,ry+=MR; ly<ry; ly>>=1,ry>>=1)
    {
        if(ly&1)
        {
            it = tree[ly].lower_bound(make_pair(lx, INT_MIN));
            goal = tree[ly].upper_bound(make_pair(rx,INT_MAX));
            while( it != goal )
            {
                printf("(%d,%d) ", it->first, it->second);
                ++it;
            }
            ly++;
        }
        if(ry&1)
        {
            r--;
            it = tree[ry].lower_bound(make_pair(lx,INT_MIN));
            goal = tree[ry].upper_bound(make_pair(rx,INT_MAX));
            while( it != goal )
            {
                printf("(%d, %d) ", it->first, it->second);
                ++it;
            }
        }
        
    }
}

int main()
{
    scanf("%d", &tc);
    while(tc--)
    {
        for(int i=0;i<MR;i++)
            tree[i].clear();
        scanf("%d %lld %d %d", &s, &r, &w, &p);
        wss = 0ll;
        for(int i=0;i<s;i++)
        {
            num ix, iy;
            scanf("%lld %lld", &ix, &iy);
            pre.insert(make_pair(ix,iy));
        }
        for(int i=0;i<w;i++)
        {
            num ix, iy;
            scanf("%lld %lld", &ix, &iy);
            x[wss]   = ix;
            y[wss++] = iy;
        }
        while( !pre.empty() )
        {
            tree[ pre.begin()->second + FX + MR ].insert(*pre.begin());
            pre.erase(pre.begin());
        }
        for(int i=MR-1;i>0;i--)
        {
            for(it=tree[i<<1].begin();it!=tree[i<<1].end();it++)
                tree[i].insert(*it);
            for(it=tree[i<<1|1].begin(); it!=tree[i<<1|1].end();it++)
                tree[i].insert(*it);
        }
        while(p--)
        {
            num ix, iy;
            scanf("%lld %lld", &ix, &iy);
            query(ix,iy);
        }
    }
}
