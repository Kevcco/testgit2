#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int trie[N*30][2],idx,cnt[N*30],pos[N*30];
int p[N];
int ans,uu,l,r;

void insert(int x,int f,int ind)
{
    int p=0;
    for(int i=k-1;i>=0;i--)
    {
        int t=x>>i&1;
        if(!trie[p][t]) trie[p][t]=++idx;
        p=trie[p][t];
        cnt[p]+=f;
    }
    if(ind) pos[p]=ind;
}

void find(int x,int q)
{
    int res=0;
    int p=0;
    int u=0;
    for(int i=k-1;i>=0;i--)
    {
        int t=x>>i&1;
        if(cnt[trie[p][t]]) res+=(1<<i),t^=1,u+=(1<<i)*t;
        p=trie[p][t^1];
    }
    if(res>ans)
    {
        ans=res;
        uu=u;
        l=q,r=pos[p];
        if(l>r) swap(l,r);
    }
}

void solve()
{
    idx=0;ans=-1;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",p+i);
        insert(p[i],1,i);
    }

    int res=0;
    for(int i=1;i<=n;i++)
    {
        insert(p[i],-1,0);
        find(p[i],i);
        insert(p[i],1,0);
    }

    printf("%d %d %d\n",l,r,uu);

    for(int i=0;i<=idx;i++) trie[i][0]=trie[i][1]=cnt[i]=pos[i]=0;
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}