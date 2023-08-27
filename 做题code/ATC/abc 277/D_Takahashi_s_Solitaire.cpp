/*
题意
现在有长为n的整数序列 ai, 0 <= ai < m, n <= 2e5, m <= 1e9
你可以任选一个元素 ai 将它删去,然后进行任意次如下操作 :
假设上一次删除的元素的元素值为 x, 任选一个元素值为 x 或 (x + 1) mod m 的元素, 将其删去。
请你最小化剩余元素的和


我们将序列排序, 那么我们一定会选择一段在 mod m 意义下后一项比前一项大 0/1 的子段, 将其删去
我们枚举这样的子段的起始位置即可
O(n)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;

void solve()
{
    cin >> n >> m;
    vector<int> a;
    ll sum=0;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        sum+=x;
        a.push_back(x);
    }

    ll res=sum;
    sort(a.begin(),a.end());

    for(int i=0;i<n;i++)
    {
        int j=i;
        ll s=0;
        int last=a[i];
        while(j<n&&a[j]<=last+1) s+=a[j],last=a[j],j++;

        if(j==n)
        {
            j=0;
            while(j<i&&a[j]+m<=last+1) s+=a[j],last=a[j]+m,j++;
            res=min(res,sum-s);
            break;
        }
        
        res=min(res,sum-s);
        i=j-1;
    }
    printf("%lld\n",res);
}

int main()
{
    solve();
    return 0;
}