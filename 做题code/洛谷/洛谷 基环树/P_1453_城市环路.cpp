// Luogu P1453
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e6+10;

int n,m;
double k;
int p[N],f[N];
vector<int> e[N];
vector<int> cyc;
bool st[N],oncyc[N];
int dp1[N][2],dp2[N][2];

bool find(int u,int fa)
{
    st[u]=1;
    f[u]=fa;
    for(auto x : e[u])
    {
        if(x==fa) continue;
        if(st[x])
        {
            int v=u;
            while(v!=f[x])
            {
                oncyc[v]=1;
                cyc.push_back(v);
                v=f[v];
            }
            return 1;
        }
        else if(find(x,u)) return 1;
    }
    return 0;
}

void dfs(int u,int fa)
{
    dp1[u][1]=p[u];
    dp1[u][0]=0;

    for(auto x : e[u])
    {
        if(x==fa) continue;
        if(oncyc[x]) continue;
        dfs(x,u);
        dp1[u][0]+=max(dp1[x][0],dp1[x][1]);
        dp1[u][1]+=dp1[x][0];
    }
}

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++) scanf("%d",p+i);
    for(int i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        x++,y++;
        e[y].push_back(x);
        e[x].push_back(y);
    }
    cin >> k;

    find(1,0);

    // 树形dp
    for(auto x : cyc) dfs(x,0);

    int ans=0,siz=cyc.size();
    dp2[0][0]=-2e9,dp2[0][1]=dp1[cyc[0]][1];
    for(int j=1;j<siz;j++)
        dp2[j][0]=max(dp2[j-1][0],dp2[j-1][1])+dp1[cyc[j]][0],
        dp2[j][1]=dp2[j-1][0]+dp1[cyc[j]][1];
    ans=dp2[siz-1][0];

    dp2[0][0]=dp1[cyc[0]][0],dp2[0][1]=-2e9;
    for(int j=1;j<siz;j++)
        dp2[j][0]=max(dp2[j-1][0],dp2[j-1][1])+dp1[cyc[j]][0],
        dp2[j][1]=dp2[j-1][0]+dp1[cyc[j]][1];
    ans=max(ans,max(dp2[siz-1][0],dp2[siz-1][1]));

    printf("%.1lf\n",ans*k);
}

int main()
{
    solve();
    return 0;
}