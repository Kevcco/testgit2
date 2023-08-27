#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=3e5+10;

int n,m,k;
int p[N];
ll cnt[N];

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++) scanf("%d",p+i);
    for(int i=1;i<=n+10;i++) cnt[i]=0;
    cnt[1]=n;
    for(int i=1;i<=n;i++)
    {
        if(p[i]>n)
        {
            puts("NO");
            return;
        }
        cnt[p[i]+1]--;
    }
    for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
    for(int i=1;i<=n;i++)
    {
        if(cnt[i]!=p[i])
        {
            puts("NO");
            return;
        }
    }
    puts("YES");
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}