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
    vector<int> e1,e0; 
    for(int i=1;i<=n;i++)
    {
        if(p[i]%2) e1.push_back(p[i]);
        else e0.push_back(p[i]);
    }
    sort(e1.begin(),e1.end());
    sort(e0.begin(),e0.end());
    int x=0,y=0;
    for(int i=1;i<=n;i++)
    {
        if(p[i]%2) p[i]=e1[x++];
        else p[i]=e0[y++];
    }
    for(int i=1;i<=n;i++)
    {
        if(p[i]<p[i-1])
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