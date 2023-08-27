#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e6+10;

int n,m;
int pr[N],p[N],pe[N],tot;
ll h[N];

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

    h[1]=1;
    for(int i=2;i<N;i++)
    {
        if(i==pe[i]) h[i]=h[i/p[i]]+(ll)i*(i-i/p[i]);
        else h[i]=h[pe[i]]*h[i/pe[i]];
    }
}

void solve()
{
    int n;
    scanf("%d",&n);
    printf("%lld\n",(ll)n*(1+h[n])/2);
}

int main()
{
    init();
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}