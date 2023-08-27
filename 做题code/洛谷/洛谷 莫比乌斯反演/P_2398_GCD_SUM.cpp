#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e5+10;

int n,m;
int pr[N],p[N],tot;
ll phi[N];

void init()
{
    p[1]=phi[1]=1;
    for(ll i=2;i<N;i++)
    {
        if(!p[i]) p[i]=i,pr[tot++]=i,phi[i]=i-1;
        for(int j=0;(ll)pr[j]*i<N;j++)
        {
            p[pr[j]*i]=pr[j];
            if(p[i]==pr[j])
            {
                phi[pr[j]*i]=phi[i]*pr[j];
                break;
            }
            phi[pr[j]*i]=phi[i]*(pr[j]-1);
        }
    }

    for(int i=1;i<N;i++) phi[i]+=phi[i-1];
}

void solve()
{
    int n;
    scanf("%d",&n);
    ll res=0;
    for(int l=1;l<=n;l++)
    {
        int r=n/(n/l);
        res+=(ll)(phi[r]-phi[l-1])*(n/l)*(n/l);
        l=r;
    }
    printf("%lld\n",res);
}

int main()
{
    init();
    int _=1;
    while(_--) solve();
    return 0;
}