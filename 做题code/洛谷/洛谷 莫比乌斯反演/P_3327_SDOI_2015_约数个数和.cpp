#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=5e4+10;

int n,m;
int pr[N],p[N],pe[N],tot;
ll d[N],mu[N];

void init()
{
    p[1]=1;
    for(ll i=2;i<N;i++)
    {
        if(!p[i]) p[i]=i,pr[tot++]=i,pe[i]=i;
        for(int j=0;(ll)pr[j]*i<N;j++)
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

    d[1]=mu[1]=1;
    for(int i=2;i<N;i++)
    {
        if(i==pe[i])
        {
            d[i]=d[i/p[i]]+1;
            if(i==p[i]) mu[i]=-1;
            else mu[i]=0;
        }
        else d[i]=d[pe[i]]*d[i/pe[i]],
        mu[i]=mu[pe[i]]*mu[i/pe[i]];
    }

    for(int i=1;i<N;i++) d[i]+=d[i-1],mu[i]+=mu[i-1];
}

void solve()
{
    int n,m;
    scanf("%d%d",&n,&m);
    if(n>m)swap(n,m);
    ll res=0;
    for(int l=1;l<=n;l++)
    {
        int r=min(n/(n/l),m/(m/l));
        res+=(mu[r]-mu[l-1])*d[n/l]*d[m/l];
        l=r;
    }
    printf("%lld\n",res);
}

int main()
{
    init();
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}