#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=5e4+10;


int n,m,d;
int pr[N],mu[N],p[N],tot;
ll inv4,inv6,inv2;
map<ll,ll> mp;

ll qmi(ll a,ll b,ll p)
{
    ll res=1;
    while(b)
    {
        if(b&1) res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}


void init()
{
    p[1]=1,mu[1]=1;
    for(ll i=2;i<N;i++)
    {
        if(!p[i]) p[i]=i,pr[tot++]=i,mu[i]=-1;
        for(int j=0;(ll)pr[j]*i<N;j++)
        {
            p[pr[j]*i]=pr[j];
            if(p[i]==pr[j])
            {
                mu[pr[j]*i]=0;
                break;
            }
            mu[pr[j]*i]=-mu[i];
        }
    }

    for(int i=1;i<N;i++) mu[i]+=mu[i-1];
}

void solve()
{
    scanf("%d%d%d",&n,&m,&d);
    n/=d,m/=d;
    if(n>m)swap(n,m);
    ll res=0;
    for(int l=1;l<=n;l++)
    {
        int r=min(n/(n/l),m/(m/l));
        res+=(ll)(mu[r]-mu[l-1])*(n/l)*(m/l);
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