#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N];

void solve()
{
    vector<int> res;
    cin >> n;
    int last=0;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        res.push_back(x);
        if(x<last) res.push_back(x);
        last=x;
    }
    printf("%d\n",res.size());
    for(auto x : res) printf("%d ",x);
    puts("");
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}