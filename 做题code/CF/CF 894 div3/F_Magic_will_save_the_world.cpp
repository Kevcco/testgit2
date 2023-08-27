#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e6+10;

int n,w,f;
int p[N];
int dp[N];

void solve()
{
    cin >> w >> f;
    cin >> n;
    int sum=0;
    for(int i=1;i<=n;i++) scanf("%d",p+i),sum+=p[i];
    for(int i=0;i<=sum;i++) dp[i]=1e9;
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=sum;j>=0;j--)
        {
            dp[j]=dp[j]+p[i];
            if(j>=p[i]) dp[j]=min(dp[j],dp[j-p[i]]);
        }
    }

    int res=1e9;
    for(int i=0;i<=sum;i++)
    {
        int t1=i/w;
        if(i%w) t1++;
        int t2=dp[i]/f;
        if(dp[i]%f) t2++;
        res=min(res,max(t1,t2));
    }
    printf("%d\n",res);
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}