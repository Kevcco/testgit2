#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e6+10;

int n,m,k;
int p[N],tot,pr[N/5];
ll phi[N],mu[N];
map<ll,ll> mpphi,mpmu;

void init()
{
    p[1]=phi[1]=mu[1]=1;
    for(int i=2;i<N;i++)
    {
        if(!p[i]) p[i]=i,pr[tot++]=i,mu[i]=-1,phi[i]=i-1;
        for(int j=0;(ll)pr[j]*i<N;j++)
        {
            p[i*pr[j]]=pr[j];
            if(p[i]==pr[j])
            {
                mu[i*pr[j]]=0;
                phi[i*pr[j]]=phi[i]*pr[j];
                break;
            }
            mu[i*pr[j]]=-mu[i];
            phi[i*pr[j]]=phi[i]*(pr[j]-1);
        }
    }

    for(int i=1;i<N;i++) mu[i]+=mu[i-1],phi[i]+=phi[i-1];

}

ll get_mu(ll n)
{
    if(n<N) return mu[n];
    if(mpmu.count(n)) return mpmu[n];
    ll res=1;
    for(ll l=2;l<=n;l++)
    {
        ll r=n/(n/l);
        res-=(r-l+1)*get_mu(n/l);
        l=r;
    }
    return mpmu[n]=res;
}

ll get_phi(ll n)
{
    if(n<N) return phi[n];
    if(mpphi.count(n)) return mpphi[n];
    ll res=n*(n+1)/2;
    for(ll l=2;l<=n;l++)
    {
        ll r=n/(n/l);
        res-=(r-l+1)*get_phi(n/l);
        l=r;
    }
    return mpphi[n]=res;
}

void solve()
{
    ll n;
    scanf("%lld",&n);
    printf("%lld %lld\n",get_phi(n),get_mu(n));
}

int main()
{
    init();
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}