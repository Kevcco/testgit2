#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
ll w[N];
ll dp[N];
vector<int> e[N];

void dfs(int i)
{
    if(dp[i]!=-1) return;
    ll sum=0;
    for(auto x : e[i])
    {
        dfs(x);
        sum+=dp[x];
    }
    dp[i]=min(w[i],sum);
}

void solve()
{
    cin >> n >> k;
    for(int i=1;i<=n;i++) dp[i]=-1,e[i].clear();
    for(int i=1;i<=n;i++) scanf("%lld",w+i);
    for(int i=1;i<=k;i++)
    {
        int x;
        scanf("%d",&x);
        dp[x]=0;
    }

    for(int i=1;i<=n;i++)
    {
        scanf("%d",&m);
        if(!m&&dp[i]==-1) dp[i]=w[i];
        for(int j=1;j<=m;j++)
        {
            int x;
            scanf("%d",&x);
            e[i].push_back(x);
        }
    }

    for(int i=1;i<=n;i++) dfs(i);
    for(int i=1;i<=n;i++) printf("%lld%c",dp[i]," \n"[i==n]);

}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}