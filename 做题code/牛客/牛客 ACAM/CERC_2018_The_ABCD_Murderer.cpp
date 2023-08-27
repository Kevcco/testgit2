#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e4+7,N=3e5+10,M=26,INF=1e9;

int n,m,idx;
int trie[N][M],go[N][M],fail[N],cnt[N];
int q[N],rr;
char str[N],s[N];
int tr[N],dp[N];

int lowbit(int x)
{
    return x&-x;
}

void add(int x,int c)
{
    for(int i=x;i<=m+1;i+=lowbit(i)) tr[i]=min(tr[i],c);
}

int sum(int l,int r)
{
    if(l>r) return INF;
    if(r-lowbit(r)+1>=l) return min(sum(l,r-lowbit(r)),tr[r]);
    return min(dp[r-1],sum(l,r-1));
}

void insert(char *s)
{
    int len=strlen(s);
    int p=0;
    for(int i=0;i<len;i++)
    {
        int t=s[i]-'a';
        if(!trie[p][t]) trie[p][t]=++idx;
        p=trie[p][t];
    }
    cnt[p]=len;
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
    cin >> n;
    scanf("%s",s);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str);
        insert(str);
    }
    build();

    for(int i=1;i<=rr;i++) cnt[q[i]]=max(cnt[q[i]],cnt[fail[q[i]]]);

    m=strlen(s);
    for(int i=1;i<=m+1;i++) tr[i]=INF;
    add(1,0);

    int p=0;
    for(int i=0;i<m;i++)
    {
        p=go[p][s[i]-'a'];
        if(!cnt[p]) dp[i+1]=INF;
        else
        {
            dp[i+1]=sum(i+2-cnt[p],i+1)+1;
            add(i+2,dp[i+1]);
        }
    }
    if(dp[m]>=INF) dp[m]=-1;
    printf("%d\n",dp[m]);
}

int main()
{
    solve();
    return 0;
}