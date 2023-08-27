#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int len[N],res[N];
char p[N],t[N];
int q[N];

void manacher()
{
    t[0]='@';
    for(int i=1;i<=n;i++) t[++m]='#',t[++m]=p[i];
    t[++m]='#',t[m+1]='~';

    int M=0,R=0;
    for(int i=1;i<=m;i++)
    {
        if(i>R) len[i]=1;
        else len[i]=min(R-i+1,len[2*M-i]);
        while(t[i+len[i]]==t[i-len[i]]) len[i]++;
        if(i+len[i]-1>R) M=i,R=i+len[i]-1;
    }
}

void solve()
{
    scanf("%s",p+1);
    n=strlen(p+1);
    manacher();

    int rr=-1;
    for(int i=1;i<=m;i++)
    {
        if((i&1)&&len[i]==1) continue;
        while(rr>=0&&i-len[i]<=q[rr]-len[q[rr]]) rr--;
        q[++rr]=i;
    }

    for(int i=1;i<=m;i++)
    {
        int l=0,r=rr;
        int t=i+len[i]-1;
        if(t==i)
        {
            res[i]=i;
            continue;
        }
        while(l<r)
        {
            int mid=l+r+1>>1;
            if(q[mid]-len[q[mid]]<=t) l=mid;
            else r=mid-1;
        }
        res[i]=q[l];
    }

    int ans=0;
    for(int i=1;i<=m;i++) ans=max(ans,res[i]-i);
    printf("%d\n",ans);

}

int main()
{
    solve();
    return 0;
}