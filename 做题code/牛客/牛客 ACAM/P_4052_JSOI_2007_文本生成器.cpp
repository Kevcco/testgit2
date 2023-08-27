#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e4+7,N=10010,M=26;

int n,m,idx;
int trie[N][M],go[N][M],fail[N],cnt[N];
int q[N],rr;
char str[N];
int dp[110][N];

void insert(char *s)
{
    int len=strlen(s);
    int p=0;
    for(int i=0;i<len;i++)
    {
        int t=s[i]-'A';
        if(!trie[p][t]) trie[p][t]=++idx;
        p=trie[p][t];
    }
    // 终止节点
    cnt[p]=1;
}

void build()
{
    rr=-1;
    q[++rr]=0;
    for(int i=0;i<=rr;i++)
    {
        int t=q[i];
        for(int j=0;j<M;j++)
        {
            if(trie[t][j])
            {
                fail[trie[t][j]]=go[fail[t]][j];
                go[t][j]=trie[t][j];
                q[++rr]=trie[t][j];
            }
            else go[t][j]=go[fail[t]][j];
        }
    }
}

void solve()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str);
        insert(str);
    }

    build();
    for(int i=1;i<=rr;i++)
        if(cnt[fail[q[i]]]) cnt[q[i]]=1;

    dp[0][0]=1;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<=idx;j++)
        {
            if(!dp[i][j]) continue;
            for(int k=0;k<M;k++)
                if(!cnt[go[j][k]]) 
                    dp[i+1][go[j][k]]=(dp[i+1][go[j][k]]+dp[i][j])%mod;
        }
    }
    
    int res=1;
    for(int i=1;i<=m;i++) res=res*26%mod;
    for(int i=0;i<=idx;i++) res-=dp[m][i],res=(res+mod)%mod;
    printf("%d\n",res);
}

int main()
{
    solve();
    return 0;
}