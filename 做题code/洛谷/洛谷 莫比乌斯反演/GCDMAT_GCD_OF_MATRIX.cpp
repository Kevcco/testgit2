#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=5e4+10;

int n,m;
int p[N],pr[N],phi[N],cnt;

void get_phi()
{
    phi[1]=1;
    for(int i=2;i<N;i++)
    {
        if(!p[i]) p[i]=i,pr[cnt++]=i,phi[i]=i-1;
        for(int j=0;pr[j]*i<N;j++)
        {
            p[pr[j]*i]=pr[j];
            if(p[i]==pr[j])
            {
                phi[i*pr[j]]=phi[i]*pr[j];
                break;
            }
            phi[i*pr[j]]=phi[i]*(pr[j]-1);
        }
    }
    for(int i=1;i<N;i++) phi[i]+=phi[i-1],phi[i]%=mod;;
}

ll block(int n,int m)
{
    ll res=0;
    int up=min(n,m);
    for(int l=1;l<=up;l++)
    {
        int r=min(n/(n/l),m/(m/l));
        res+=(ll)(phi[r]-phi[l-1])*(n/l)*(m/l);
        res=(res%mod+mod)%mod;
        l=r;
    }
    return res;
}

void solve()
{
    int a,b,c,d;
    scanf("%d%d%d%d",&a,&c,&b,&d);
    ll res=block(b,d)-block(a-1,d)-block(b,c-1)+block(a-1,c-1);
    res=(res%mod+mod)%mod;
    printf("%lld\n",res);
}

int main()
{
    get_phi();
    int _;
    cin >> _;
    cin >> n >> m;
    while(_--) solve();
    return 0;
}