#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=6e5+10;

int n,m,k;
ll p[N];
ll d[N];
int cnt[N];

void solve()
{
    cin >> n;
    for(int i=1;i<n;i++) scanf("%lld",p+i),cnt[i]=0;
    cnt[n]=0;
    for(int i=1;i<n;i++)
    {
        d[i]=p[i]-p[i-1];
        if(d[i]>=N)
        {
            puts("NO");
            return;
        }
    }
    for(int i=1;i<n;i++) cnt[d[i]]++;

    int ans=0,p1=0,p2=0;
    for(int i=1;i<=n;i++)
    {
        if(!cnt[i])
        {
            ans++;
            if(!p1) p1=i;
            else p2=i;
        }
    }
    if(ans>2)
    {
        puts("NO");
        return;
    }
    if(ans==1)
    {
        puts("YES");
        return;
    }

    bool f=0;
    for(int i=1;i<n;i++)
    {
        if(d[i]>n||cnt[d[i]]>1)
        {
            if(p1+p2==d[i])
            {
                f=1;
                break;
            }
        }
    }
    if(f) puts("YES");
    else puts("NO");
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}