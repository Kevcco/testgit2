#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int h[N],p[N];
vector<array<int,3>> edge;
vector<int> e[N];
int f[19][N],maxh[19][N],depth[N];
bool st[N];

int find(int x)
{
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}

void dfs(int u,int fa)
{
    st[u]=1;
    depth[u]=depth[fa]+1;
    f[0][u]=fa;
    maxh[0][u]=max(h[u],h[fa]);
    for(auto v : e[u])
    {
        if(v==fa) continue;
        dfs(v,u);
    }
}

int query(int a,int b)
{
    if(depth[a]<depth[b]) swap(a,b);
    int d=depth[a]-depth[b];
    int maxv=0;
    for(int i=18;i>=0;i--)
        if(d>>i&1) maxv=max(maxv,maxh[i][a]),a=f[i][a];
    if(a==b) return maxv;
    for(int i=18;i>=0;i--)
    {
        if(f[i][a]!=f[i][b])
        {
            maxv=max(maxv,maxh[i][a]);
            maxv=max(maxv,maxh[i][b]);
            a=f[i][a];
            b=f[i][b];
        }
    }
    maxv=max(maxv,max(maxh[0][a],maxh[0][b]));
    return maxv;
}

void solve()
{
    edge.clear();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",h+i),p[i]=i,e[i].clear(),st[i]=0;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        edge.push_back({max(h[x],h[y]),x,y});
    }

    sort(edge.begin(),edge.end());
    for(auto a : edge)
    {
        int x=find(a[1]),y=find(a[2]);
        if(x==y) continue;
        p[x]=y;
        e[a[1]].push_back(a[2]);
        e[a[2]].push_back(a[1]);
    }

    for(int i=1;i<=n;i++) if(!st[i]) dfs(i,0);
    for(int j=1;j<19;j++)
        for(int i=1;i<=n;i++)
            maxh[j][i]=max(maxh[j-1][i],maxh[j-1][f[j-1][i]]),
            f[j][i]=f[j-1][f[j-1][i]];

    scanf("%d",&k);
    while(k--)
    {
        int a,b,x;
        scanf("%d%d%d",&a,&b,&x);

        if(find(a)!=find(b))
        {
            puts("NO");
            continue;
        }
        int t=query(a,b);
        if(h[a]+x>=t) puts("YES");
        else puts("NO");
    }
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}