#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e5+10;

int n,m,tot;
int trie[N][26],fail[N],go[N][26],idx;
int q[N],rr;
char s[N];
int pos[N],res[N];
vector<pii> query[N];
vector<int> e[N];
int tr[N],l[N],r[N],tt;

int lowbit(int x)
{
    return x&-x;
}

void add(int x,int c)
{
    for(int i=x;i<=tt;i+=lowbit(i)) tr[i]+=c;
}

int sum(int x)
{
    int res=0;
    for(int i=x;i;i-=lowbit(i)) res+=tr[i];
    return res;
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
    l[u]=++tt;
    for(auto x : e[u]) dfs(x);
    r[u]=tt;
}

void get_ans(int u)
{
    add(l[u],1);
    for(auto x : query[u])
    {
        int v=x.first,id=x.second;
        int ans=sum(r[v])-sum(l[v]-1);
        res[id]=ans;
    }
    for(int i=0;i<26;i++)
        if(trie[u][i]) get_ans(trie[u][i]);
    add(l[u],-1);
}

void solve()
{
    scanf("%s",s);
    n=strlen(s);
    stack<int> sta;
    int p=0;
    for(int i=0;i<n;i++)
    {
        if(s[i]=='P') pos[++tot]=p;
        else if(s[i]=='B')
        {
            p=sta.top();
            sta.pop();
        }
        else
        {
            int t=s[i]-'a';
            if(!trie[p][t]) trie[p][t]=++idx;
            sta.push(p);
            p=trie[p][t];
        }
    }

    build();
    for(int i=1;i<=idx;i++) e[fail[i]].push_back(i);
    dfs(0);

    cin >> m;
    for(int i=1;i<=m;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        query[pos[b]].push_back({pos[a],i});
    }

    get_ans(0);
    for(int i=1;i<=m;i++) printf("%d\n",res[i]);
}

int main()
{
    solve();
    return 0;
}