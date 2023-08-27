//https://ac.nowcoder.com/acm/contest/29086/H
// ACAM上fail树的dfs序建可持久化线段树
#include <bits/stdc++.h>

using namespace std;

const int N=2e5+10,INF=1e9+5;

int n,m,times;
int root[N],a[N];
int trie[N][26],fail[N],go[N][26],idx;
int tag[N],pos[N];
int q[N],rr;
string s[N];
vector<int> e[N];
int LL[N],RR[N],tot;

struct node
{
    int l,r;
    int cnt;
}tr[N*40];

void insert(int u)
{
    int p=0;
    for(int i=0;i<s[u].size();i++)
    {
        int t=s[u][i]-'a';
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

void pushup(int u)
{
    tr[u].cnt=tr[tr[u].l].cnt+tr[tr[u].r].cnt;
}

void modify(int p,int q,int L,int R,int x)
{
    tr[q]=tr[p];
    if(L==R)
    {
        tr[q].cnt++;
        return;
    }
    
    int mid=L+R>>1;
    if(x>mid)
    {
        tr[q].r=++times;
        modify(tr[p].r,tr[q].r,mid+1,R,x);
    }
    else
    {
        tr[q].l=++times;
        modify(tr[p].l,tr[q].l,L,mid,x);
    }
    pushup(q);
}

int query(int p,int L,int R,int l,int r)
{
    if(L>=l&&R<=r) return tr[p].cnt;
    int res=0;
    int mid=L+R>>1;
    if(l<=mid) res+=query(tr[p].l,L,mid,l,r);
    if(r>mid) res+=query(tr[p].r,mid+1,R,l,r);
    return res;
}

void dfs(int u)
{
    LL[u]=++tot;
    for(auto x : e[u]) dfs(x);
    RR[u]=tot;
}

void solve()
{
    int tt=-1;
    cin >> n >> m;
    root[++tt]=++times;
    for(int i=1;i<=n;i++)
    {
        cin >> s[i];
        insert(i);
    }
    build();
    for(int i=1;i<=idx;i++) e[fail[i]].push_back(i);
    dfs(0);

    pos[0]=0;
    for(int i=1;i<=n;i++)
    {
        int p=0;
        for(int j=0;j<s[i].size();j++)
        {
            int t=s[i][j]-'a';
            p=trie[p][t];
            root[++tt]=++times;
            modify(root[tt-1],root[tt],1,idx+1,LL[p]);
        }
        pos[i]=tt;
    }
    
    while(m--)
    {
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        int res=query(root[pos[r]],1,idx+1,LL[tag[k]],RR[tag[k]]);
        res-=query(root[pos[l-1]],1,idx+1,LL[tag[k]],RR[tag[k]]);
        printf("%d\n",res);
    }    
}

int main()
{
    solve();
    return 0;
}