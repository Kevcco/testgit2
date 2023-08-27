#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2010;

int n,m;
int p[N],a[N],b[N];
int inva[N],invb[N],siz[N],inv;
ll dp[N][N],res[N],sum;
vector<int> e[N];

int qmi(int a,int k,int p)
{
    int res=1;
    while(k)
    {
        if(k&1) res=(ll)res*a%p;
        a=(ll)a*a%p;
        k>>=1;
    }
    return res;
}

void dfs(int u,int fa,int pre)
{
    siz[u]=1;
    if(u!=1&&e[u].size()==1)
    {
        dp[u][0]=(ll)(1-(ll)a[u]*invb[u]%mod)%mod,dp[u][0]=(dp[u][0]+mod)%mod;
        dp[u][1]=(ll)a[u]*invb[u]%mod;
        return;
    }
    dp[u][0]=1;
    for(auto x : e[u])
    {
        if(x==fa) continue;
        if(u!=1) dfs(x,u,(ll)pre*a[u]%mod*invb[u]%mod);
        else dfs(x,u,1);
        for(int j=siz[u]+siz[x];j>=0;j--)
            for(int k=max(0,j-siz[u]);k<=min(j,siz[x]);k++) 
            {
                dp[u][j]+=(ll)dp[j-k][0]*dp[x][k]%mod;
                dp[u][j]%=mod;
            }

        siz[u]+=siz[x];
    }

    for(int i=0;i<n;i++) dp[u][i]=dp[u][i]*a[u]%mod*invb[u]%mod;
    for(int i=n;i>=1;i--) dp[u][i]=dp[u][i-1];
    if(u!=1) dp[u][0]=1-(ll)a[u]*invb[u]%mod,dp[u][0]=(dp[u][0]+mod)%mod;
    else dp[u][0]=0;
}

void dfs2(int u,int fa)
{
    for(auto x : e[u])
    {
        if(x==fa) continue;
        for(int i=1;i<=n;i++) dp[x][i]=dp[u][i]*b[x]%mod*inva[x]%mod*a[u]%mod*invb[u]%mod;
        for(int i=1;i<=n;i++) res[i]+=dp[x][i]*p[x]%mod*inv%mod,res[i]%=mod;
        dfs2(x,u);
    }
}

void solve()
{
    cin >> n;
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",p+i);
        sum+=p[i];
        scanf("%d%d",a+i,b+i);
        inva[i]=qmi(a[i],mod-2,mod);
        invb[i]=qmi(b[i],mod-2,mod);
    }
    inv=qmi(sum,mod-2,mod);
    dfs(1,0,1);
    for(int i=1;i<=n;i++) res[i]=dp[1][i]*p[1]%mod*inv%mod;
    dfs2(1,0);
    for(int i=1;i<=n;i++) printf("%lld\n",res[i]);
}

int main()
{
    solve();
    return 0;
}