#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<string,int> pii;

const int mod=1e9+7,N=3e6+10,M=26;

int n,m,tot;
int trie[N][M],fail[N],go[N][M],idx;
char str[N];
int tag[N];
int q[N],rr;
vector<pii> query;
vector<int> e[N];
int l[N],r[N],tr[N];

int lowbit(int x)
{
    return x&-x;
}

void add(int x,int c)
{
    for(int i=x;i<=idx+1;i+=lowbit(i)) tr[i]+=c;
}

int sum(int x)
{
    int res=0;
    for(int i=x;i;i-=lowbit(i)) res+=tr[i];
    return res;
}

void insert(int u)
{
    int len=strlen(str);
    int p=0;
    for(int i=0;i<len;i++)
    {
        int t=str[i]-'a';
        if(!trie[p][t]) trie[p][t]=++idx;
        p=trie[p][t];
    }
    tag[u]=p;
}

void build()
{
    rr=-1;
    q[++rr]=0;
    for(int i=0;i<=rr;i++)
    {
        int t=q[i];
        for(int j=0;j<26;j++)
        {
            if(trie[t][j])
            {
                fail[trie[t][j]]=go[fail[t]][j];
                go[t][j]=trie[t][j];
                q[++rr]=trie[t][j];
            }
            else go[t][j]=go[fail[t]][j];
        }
    }
}

void dfs(int u)
{
    l[u]=++tot;
    for(auto x : e[u]) dfs(x);
    r[u]=tot;
}

void solve()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str);
        insert(i);
    }
    for(int i=1;i<=m;i++)
    {
        int ty;
        scanf("%d%s",&ty,str);
        if(ty==1) n++,insert(n);
        else query.push_back({str,n});
    }

    build();
    for(int i=1;i<=idx;i++) e[fail[i]].push_back(i);
    dfs(0);

    int now=0;
    for(auto x : query)
    {
        int times=x.second;
        string s=x.first;
        while(now<times)
        {
            now++;
            int t=tag[now];
            add(l[t],1);
            add(r[t]+1,-1);
        }
        int res=0;
        int p=0;
        for(auto c : s)
        {
            int t=c-'a';
            p=go[p][t];
            res+=sum(l[p]);
        }
        printf("%d\n",res);
    }

    query.clear();
    for(int i=0;i<=idx+1;i++)
    {
        e[i].clear();
        tr[i]=0;
        fail[i]=0;
        for(int j=0;j<M;j++)
            trie[i][j]=go[i][j]=0;
    }
    idx=tot=0;
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}