// Luogu 1659
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=19930726,N=1e6+10;

ll n,m,k;
int len[N*2];
ll cnt[N];
char s[N],t[N*2];

int qmi(int a,ll k,int p)
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

void manacher()
{
    t[0]='@';
    t[++m]='$';
    for(int i=1;i<=n;i++) t[++m]=s[i],t[++m]='$';
    t[m+1]='~';

    int M=0,R=0;
    for(int i=1;i<=m;i++)
    {
        if(i>R) len[i]=1;
        else len[i]=min(len[2*M-i],R-i+1);
        while(t[i-len[i]]==t[i+len[i]]) len[i]++;
        if(i+len[i]-1>R) M=i,R=i+len[i]-1;
    }

}

void solve()
{
    cin >> n >> k;
    scanf("%s",s+1);

    manacher();
    for(int i=1;i<=m;i++) if((len[i]-1)%2) cnt[len[i]-1]++;

    int res=1;
    for(int i=n;i>=1;i--)
    {
        if(cnt[i]<k)
        {
            k-=cnt[i];
            res=(ll)res*qmi(i,cnt[i],mod)%mod;
            if(i>1) cnt[i-2]+=cnt[i];
        }
        else
        {
            res=(ll)res*qmi(i,k,mod)%mod;
            k=0;
            break;
        }
    }
    if(k) printf("-1\n");
    else printf("%d\n",res);
}

int main()
{
    solve();
    return 0;
}