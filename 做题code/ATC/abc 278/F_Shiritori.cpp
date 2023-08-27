/*
题意
博弈 给定n个字符串 n <= 16
每次操作需要选择一个从没选择过的字符串
并且满足选择的字符串的首项等于上次选择的字符串的尾项(第一次选择除外)
无法操作的输,问谁赢


观察到n很小,直接状压dp剩余的字符串集和上次选择的尾字母即可
转移就是根据 P/N态的性质:能转移到P态的是N态,否则是P态
O(2^n * |@| * n)  其中|@|为字符集大小
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
string s[20];
int dp[1<<17][26];

void solve()
{
    cin >> n;
    for(int i=0;i<n;i++) cin >> s[i];

    for(int i=1;i<1<<n;i++)
    {
        for(int j=0;j<26;j++)
        {
            for(int k=0;k<n;k++)
            {
                if((i>>k&1)&&s[k][0]-'a'==j)
                {
                    if(!dp[i^(1<<k)][s[k][s[k].size()-1]-'a'])
                    {
                        dp[i][j]=1;
                        break;
                    }
                }
            }
        }
    }

    int res=0;
    for(int i=0;i<26;i++) res|=dp[(1<<n)-1][i];
    if(res) puts("First");
    else puts("Second");
}

int main()
{
    solve();
    return 0;
}