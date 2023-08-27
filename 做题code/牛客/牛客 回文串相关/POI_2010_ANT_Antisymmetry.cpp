#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=5e5+10;

int n,m,k;
int len[N*2];
char p[N],t[N*2];

void manacher()
{
    t[0]='@';
    for(int i=1;i<=n;i++) t[++m]='#',t[++m]=p[i];
    t[++m]='#',t[m+1]='~';

    int M=0,R=0;
    for(int i=1;i<=m;i++)
    {
        if(!(i&1)) continue;
        if(i>R) len[i]=1;
        else len[i]=min(R-i+1,len[2*M-i]);
        while((t[i+len[i]]=='0'&&t[i-len[i]]=='1')||(t[i+len[i]]=='1'&&t[i-len[i]]=='0')||(t[i+len[i]]=='#'&&t[i-len[i]]=='#')) len[i]++;
        if(i+len[i]-1>R) M=i,R=i+len[i]-1;
    }
}

void solve()
{
    cin >> n;
    scanf("%s",p+1);

    manacher();
    
    ll res=0;
    for(int i=1;i<=m;i+=2) res+=len[i]/2;
    printf("%lld\n",res);
}

int main()
{
    solve();
    return 0;
}