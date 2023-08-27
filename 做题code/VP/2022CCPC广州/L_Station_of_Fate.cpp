#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=998244353,N=1e5+10;

int n,m,k;
int f[N],inf[N];

int qmi(int a,int k,int p)
{
    int res=1;
    while(k)
    {
        if(k&1) res=(ll)res*a%p;
        a=(ll)a*a%p;
        k>>=1;
    }
    return res;
}

void init()
{
    f[0]=1;
    for(int i=1;i<N;i++) f[i]=(ll)f[i-1]*i%mod;
    inf[N-1]=qmi(f[N-1],mod-2,mod);
    for(int i=N-2;i>=0;i--) inf[i]=(ll)inf[i+1]*(i+1)%mod;
}

int c(int n,int m)
{
    return (ll)f[n]*inf[m]%mod*inf[n-m]%mod;
}

void solve()
{
    cin >> n >> m;
    int res=f[n];
    res=(ll)res*c(n-1,m-1)%mod;
    printf("%d\n",res);
}

int main()
{
    init();
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}