/*
题意
交互 + 博弈
给定长为 n 的线段, n <= 2000
每次操作需要选择一段长度为[l,r]之间的连续子线段, 并将这线段删去, 不能操作的输
现在给定 n,l,r, 需要知道先手胜还是后手胜,选择好先后手后,还要和系统交互着赢下游戏


我们朴素地去dfs求sg值, 时间复杂度是 O(n * n * (r-l))的, 显然无法接受
如何优化?
sg[x] = mex ({sg[i]^sg[j]}), 其中i,j满足  x-r <= i+j <= x-l
看到 i+j 的限制条件, 我们想到对于所有的值 val, 
按照i+j的大小顺序存储所有满足 sg[i] ^ sg[j] = val 的(i,j)对
那么求mex时, 只要从0开始检查每个val存储的对中是否存在满足限制的(i,j)即可
二分即可做到
那么val的范围是多少? 可以证明 gi <= i 因此val开[1,n]即可
证明可以用数学归纳 : sg[0] = 0, 假设 sg[i] <= i, 0 <= i <= k
那么 sg[k+1] = mex ({sg[i]^sg[j]}), 而 i + j < k + 1
因此sg[i]^sg[j] <= sg[i] + sg[j] <= i + j < k + 1, 故sg[k+1] <= k + 1
最优策略和求sg值类似的做法即可解决 O(n * n * logn)

其实还有更巧妙的做法: Tweedledum-Tweedledee Strategy
我的理解是后手下模仿棋, 或者说镜像操作
假如给定两条长为n的线段, 那么后手必赢, 
因为先手在一条线段上操作,后手总能在另一条线段上执行同样的操作, 最终只能是先手无法操作
这由此启发, 只要我们先手在中间切掉一段, 切成两条一样长的线段, 那么先手就赢了
那么只要 r > l || n和l奇偶性一致, 就一定可以做到
那么只剩一种情况 l=r && 奇偶性不同, 这时只要朴素去求sg值即可 O(n*n)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2010;

int n,l,r;
int sg[N];
int x,y,sg_now;
set<pii> s;

void dfs(int x)
{
    set<int> ss;
    for(int i=1;i+l-1<=x;i++)
    {
        int t1=i-1,t2=x-(i+l-1);
        ss.insert(sg[t1]^sg[t2]);
    }
    while(ss.count(sg[x])) sg[x]++;
}

int get_pos()
{
    for(auto seg : s)
    {
        int L=seg.first,R=seg.second,len=R-L+1;
        for(int i=L;i+l-1<=R;i++)
        {
            int t1=i-L,t2=R-(i+l-1);
            if(!(sg_now^sg[len]^sg[t1]^sg[t2]))
                return i;
        }
    }
    return 0;
}

void get_sg()
{
    for(int i=l;i<=n;i++) dfs(i);

    if(sg[n])
    {
        printf("First\n");
        s.insert({1,n});
        sg_now=sg[n];
    }
    else
    {
        printf("Second\n");
        fflush(stdout);
        scanf("%d%d",&x,&y);
        if(x==0||x==-1) return;
        if(x-1>=l) s.insert({1,x-1});
        if(n-x-y+1>=l) s.insert({x+y,n});
        sg_now=sg[x-1]^sg[n-x-y+1];
    }

    while(1)
    {
        int pos=get_pos();
        for(auto seg : s)
        {
            int L=seg.first,R=seg.second,len=R-L+1;
            if(L>pos||R<pos) continue;

            int t1=pos-L,t2=R-(pos+l-1);
            printf("%d %d\n",pos,l);
            if(t1>=l) s.insert({L,pos-1});
            if(t2>=l) s.insert({pos+l,R});
            s.erase(seg);
            sg_now=0;
            break;
        }

        fflush(stdout);
        scanf("%d%d",&x,&y);
        if(x==0||x==-1) break;

        for(auto seg : s)
        {
            int L=seg.first,R=seg.second,len=R-L+1;
            if(L>x||R<x) continue;

            int t1=x-L,t2=R-(x+l-1);
            if(t1>=l) s.insert({L,x-1});
            if(t2>=l) s.insert({x+l,R});
            s.erase(seg);
            sg_now=sg[len]^sg[t1]^sg[t2];
            break;
        }
    }
}

void Tweedledum_Tweedledee()
{
    int len=l+((n&1)!=(l&1)),pos=(n-len)/2+1;
    printf("First\n%d %d\n",pos,len); 
    fflush(stdout);
    while(1)
    {
        scanf("%d%d",&x,&y); 
        if(x==0||x==-1) break;
        if(x<pos) printf("%d %d\n",x+len+pos-1,y);
        else printf("%d %d\n",x-len-pos+1,y); 
        fflush(stdout); 
    }
}

void solve()
{
    scanf("%d%d%d",&n,&l,&r);
    if(l==r&&(n-l)%2) get_sg();
    else Tweedledum_Tweedledee();
}

int main()
{
    solve();
    return 0;
}