// Luogu P4381
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e6+10;

int n,m,p[N],L[N];
vector<pii> e[N];
bool st[N],oncyc[N];
ll dp[N][2];
ll s[N*2],suff[N],pre[N],ans;

void dfs(int u)
{
    st[u]=1;
    for(auto t : e[u])
    {
        int x=t.first,w=t.second;
        if(oncyc[x]) continue;
        dfs(x);
        if(dp[x][0]+w>dp[u][0]) dp[u][1]=dp[u][0],dp[u][0]=dp[x][0]+w;
        else if(dp[x][0]+w>dp[u][1]) dp[u][1]=dp[x][0]+w;
    }
    ans=max(ans,dp[u][0]+dp[u][1]);
}

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d%d",&y,&x);
        p[i]=y;
        L[i]=x;
        e[y].push_back({i,x});
    }

    ll res=0;
    for(int i=1;i<=n;i++)
    {
        if(st[i]) continue;

        int u=i;
        while(!st[u]) st[u]=1,u=p[u];

        vector<int> cyc;
        cyc.push_back(u);
        oncyc[u]=1;
        int v=p[u];
        while(v!=u) cyc.push_back(v),oncyc[v]=1,v=p[v];

        ans=0;
        for(auto x : cyc) dfs(x);
        m=cyc.size();
        for(int i=0;i<m-1;i++) s[i+2]=s[i+1]+L[cyc[i]];
        s[m+1]=s[m]+L[cyc[m-1]];
        for(int i=0;i<m-1;i++) s[i+2+m]=s[i+1+m]+L[cyc[i]];
        suff[m+1]=-1e18;
        for(int i=m;i>=1;i--) suff[i]=max(suff[i+1],dp[cyc[i-1]][0]-s[i]);
        pre[0]=-1e18;
        for(int i=1;i<=m;i++) pre[i]=max(pre[i-1],dp[cyc[i-1]][0]-s[i+m]);
        for(int i=1;i<=m;i++)
            ans=max(ans,max(suff[i+1],pre[i-1])+dp[cyc[i-1]][0]+s[i+m]);

        res+=ans;
    }

    printf("%lld\n",res);
}

int main()
{
    solve();
    return 0;
}