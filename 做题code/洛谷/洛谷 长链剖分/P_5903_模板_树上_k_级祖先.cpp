#include <bits/stdc++.h>
#define ui unsigned int

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=5e5+10;

int n,q,root;
vector<int> e[N];
int h[N],son[N],depth[N];
int fa[20][N];
int l[N],r[N],id[N],tot,top[N];
vector<int> up[N],down[N];
ui s;

inline ui get(ui x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x; 
}

void dfs1(int u,int f)
{
    depth[u]=depth[f]+1;
    h[u]=0,fa[0][u]=f;
    for(auto v: e[u])
    {
        dfs1(v,u);
        if(h[v]>h[son[u]]) son[u]=v;
        h[u]=max(h[u],h[v]+1);
    }
}

void dfs2(int u,int f,int t)
{
    top[u]=t;
    l[u]=++tot;
    id[tot]=u;
    if(u==t)
    {
        int v=u;
        for(int i=0;i<=h[u];i++) up[u].push_back(v),v=fa[0][v];
        v=u;
        for(int i=0;i<=h[u];i++) down[u].push_back(v),v=son[v];
    }
    if(son[u]) dfs2(son[u],u,t);
    for(auto v : e[u]) if(v!=son[u]) dfs2(v,u,v);
    r[u]=tot;
}

int ask(int u,int k)
{
    if(!k) return u;
    int lg=31-__builtin_clz(k);
    u=fa[lg][u];
    k-=(1<<lg);
    k-=h[top[u]]-h[u];
    u=top[u];
    if(k>=0) return up[u][k];
    return down[u][-k];
}

void solve()
{
    cin >> n >> q >> s;
    for(int i=1;i<=n;i++)
    {
        int f;
        scanf("%d",&f);
        if(f) e[f].push_back(i);
        else root=i;
    }

    dfs1(root,0);
    dfs2(root,0,root);

    for(int j=1;j<20;j++)
        for(int i=1;i<=n;i++)
            fa[j][i]=fa[j-1][fa[j-1][i]];
    
    ll res=0;
    ui ans=0;
    for(int i=1;i<=q;i++)
    {
        int x=(get(s)^ans)%n+1;
        int k=(get(s)^ans)%depth[x];
        ans=ask(x,k);
        res^=(ll)i*ans;
    }
    printf("%lld\n",res);
}

int main()
{
    solve();
    return 0;
}