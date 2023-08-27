// Luogu P3899
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e5+10;

int n,m;
vector<int> e[N];
vector<ll> dp[N];
int son[N],h[N],depth[N],siz[N];
ll ans[N],tag[N];
vector<array<int,2>> query[N];

void dfs(int u,int fa)
{
    depth[u]=depth[fa]+1;
    siz[u]=1;
    for(auto j : e[u])
    {
        if(j==fa) continue;
        dfs(j,u);
        siz[u]+=siz[j];
        if(h[j]>=h[son[u]]) son[u]=j;
        h[u]=max(h[u],h[j]+1);    
    }
}

void dfs2(int u,int fa)
{
    if(son[u])
    {
        dfs2(son[u],u);
        dp[u].swap(dp[son[u]]);
        dp[u].push_back(0);
        tag[u]+=tag[son[u]]+siz[son[u]]-1;
        dp[u][h[u]-1]-=tag[son[u]];
    }
    else dp[u].push_back(0),tag[u]=0;

    for(auto j : e[u])
    {
        if(j==fa||j==son[u]) continue;
        dfs2(j,u);
        tag[u]+=tag[j]+siz[j]-1;
        dp[u][h[u]-1]-=tag[j];
        for(int i=0;i<h[j];i++)
        {
            int t=h[u]-h[j]+i-1;
            dp[u][t]+=dp[j][i];
        }
    }

    for(auto q : query[u]) ans[q[1]]+=tag[u]+dp[u][h[u]-min(h[u],q[0])];
}

int main()
{
    cin >> n >> m;
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }

    dfs(1,0);
    for(int i=1;i<=m;i++)
    {
        int p,k;
        scanf("%d%d",&p,&k);
        query[p].push_back({k,i});
        ans[i]+=(ll)(siz[p]-1)*min(k,depth[p]-1);
    }

    dfs2(1,0);
    
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    
    return 0;
}