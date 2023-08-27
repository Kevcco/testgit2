// CF 1009F
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e6+10;

int n;
vector<int> e[N],dp[N];
int son[N],h[N],depth[N];
int ans[N];

void dfs(int u,int fa)
{
    depth[u]=depth[fa]+1;
    for(auto j : e[u])
    {
        if(j==fa) continue;
        dfs(j,u);
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
        dp[u].push_back(1);
        ans[u]=ans[son[u]];
        if(dp[u][ans[u]]==1) ans[u]=h[u];
    }
    else dp[u].push_back(1),ans[u]=0;

    for(auto j : e[u])
    {
        if(j==fa||j==son[u]) continue;
        dfs2(j,u);
        for(int i=0;i<=h[j];i++)
        {
            int t=h[u]-h[j]+i-1;
            dp[u][t]+=dp[j][i];
            if(dp[u][t]>dp[u][ans[u]]) ans[u]=t;
            else if(dp[u][t]==dp[u][ans[u]]) ans[u]=max(ans[u],t);
        }
    }
}

int main()
{
    cin >> n;
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    
    dfs(1,0);
    dfs2(1,0);
    
    for(int i=1;i<=n;i++) printf("%d\n",h[i]-ans[i]);
    
    return 0;
}