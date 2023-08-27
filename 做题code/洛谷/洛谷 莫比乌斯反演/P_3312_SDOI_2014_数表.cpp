#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned int u32;
typedef pair<int,int> pii;

const int N=1e5+10;

int last;
u32 pr[N],pe[N],sigma[N],p[N],mu[N],tot;
u32 res[N],tr[N];
vector<array<int,4>> query;
vector<pair<u32,int>> f;

int lowbit(int x)
{
    return x&-x;
}

void add(int x,int c)
{
    for(int i=x;i<N;i+=lowbit(i)) tr[i]+=c;
}

u32 sum(int x)
{
    u32 res=0;
    for(int i=x;i;i-=lowbit(i)) res+=tr[i];
    return res;
}

void init()
{
    p[1]=1;
    for(int i=2;i<N;i++)
    {
        if(!p[i]) p[i]=i,pr[tot++]=i,pe[i]=i;
        for(int j=0;pr[j]*i<N;j++)
        {
            p[pr[j]*i]=pr[j];
            if(p[i]==pr[j])
            {
                pe[pr[j]*i]=pe[i]*pr[j];
                break;      
            }
            pe[pr[j]*i]=pr[j];
        }
    }

    sigma[1]=mu[1]=1;
    for(int i=2;i<N;i++)
    {
        if(i==pe[i])
        {
            sigma[i]=sigma[i/p[i]]+i;
            if(i==p[i]) mu[i]=-1;
            else mu[i]=0;
        }
        else sigma[i]=sigma[i/pe[i]]*sigma[pe[i]],mu[i]=mu[i/pe[i]]*mu[pe[i]];
    }

    for(int i=1;i<N;i++) f.push_back({sigma[i],i});
    sort(f.begin(),f.end());
}

void ins(int r)
{
    while(last<f.size()&&f[last].first<=r)
    {
        u32 t=f[last].first,pos=f[last].second;
        for(int j=pos;j<N;j+=pos) add(j,t*mu[j/pos]);
        last++;
    }
}

void solve(int n,int m,int id)
{
    if(n>m)swap(n,m);
    u32 ans=0;
    for(int l=1;l<=n;l++)
    {
        int r=min(n/(n/l),m/(m/l));
        ans+=(sum(r)-sum(l-1))*(n/l)*(m/l);
        l=r;
    }
    res[id]=ans;
}

int main()
{
    init();
    int _;
    cin >> _;
    for(int i=1;i<=_;i++)
    {
        int n,m,a;
        scanf("%d%d%d",&n,&m,&a);
        query.push_back({a,n,m,i});
    }
    sort(query.begin(),query.end());
    for(auto q : query)
    {
        ins(q[0]);
        solve(q[1],q[2],q[3]);
    }
    for(int i=1;i<=_;i++) printf("%d\n",res[i]%(1ll<<31));
    return 0;
}