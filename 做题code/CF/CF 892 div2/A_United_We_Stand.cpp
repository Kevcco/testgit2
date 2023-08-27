#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N];

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++) scanf("%d",p+i);
    bool f=1;
    for(int i=2;i<=n;i++)
        if(p[i]!=p[i-1]) f=0;
    if(f) puts("-1");
    else
    {
        sort(p+1,p+n+1);
        vector<int> b,c;
        b.push_back(p[1]);
        int i=2;
        while(p[i]==p[1]) b.push_back(p[i]),i++;
        for(int j=i;j<=n;j++) c.push_back(p[j]);
        printf("%d %d\n",b.size(),c.size());
        for(auto x : b) printf("%d ",x);
        puts("");
        for(auto x : c) printf("%d ",x);
        puts("");
    }
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}