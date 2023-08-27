/*
题意
给定一张(n,m)无向图, n,m <= 2e5
每条边有一个边权0/1, 1代表通,0代表不通
现在有k个点上有机关, 机关的作用是使所有边的边权取反(0->1,1->0)
处于存在机关的点时,可以触发任意次机关
询问从点1走到点n最少需要几步


我们在普通BFS的基础上再增添一维 0/1, 1代表到达此点时,机关共使用了偶数次,0代表奇数次
在BFS更新时, 区分这个点有机关和无机关两种情况即可
O(n+m)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N];
bool st[N];
vector<pii> e[N];
int d[N][2];

void solve()
{
    cin >> n >> m >> k;
    for(int i=1;i<=m;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        e[a].push_back({b,c});
        e[b].push_back({a,c});
    }
    for(int i=1;i<=k;i++)
    {
        int x;
        scanf("%d",&x);
        st[x]=1;
    }

    memset(d,0x3f,sizeof d);
    d[1][1]=0;
    queue<pii> q;
    q.push({1,1});
    if(st[1])d[1][0]=0,q.push({1,0});
    while(!q.empty())
    {
        auto t=q.front();
        q.pop();
        int v=t.first,tt=t.second;
        if(!st[v])
        {
            for(auto x : e[v])
            {
                int a=x.first,b=x.second;
                if(b^tt) continue;
                if(d[a][tt]>d[v][tt]+1)
                {
                    d[a][tt]=d[v][tt]+1;
                    q.push({a,tt});
                }
            }
        }
        else
        {
            for(auto x : e[v])
            {
                int a=x.first,b=x.second;
                if(d[a][b]>d[v][tt]+1)
                {
                    d[a][b]=d[v][tt]+1;
                    q.push({a,b});
                }
            } 
        }
    }
    int res=min(d[n][0],d[n][1]);
    if(res==0x3f3f3f3f) res=-1;
    printf("%d\n",res);
}

int main()
{
    solve();
    return 0;
}