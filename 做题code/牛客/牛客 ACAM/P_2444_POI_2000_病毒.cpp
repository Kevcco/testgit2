#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e4+7,N=3e4+10,M=2;

int n,m,idx;
int trie[N][M],go[N][M],fail[N],cnt[N];
int q[N],rr;
char str[N];
bool st[N],ins[N];

void insert(char *s)
{
    int len=strlen(s);
    int p=0;
    for(int i=0;i<len;i++)
    {
        int t=s[i]-'0';
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

bool dfs(int u)
{
    st[u]=1;
    ins[u]=1;
    for(int i=0;i<M;i++)
    {
        if(cnt[go[u][i]]) continue;
        if(st[go[u][i]])
        {
            if(ins[go[u][i]]) return 1;
        }
        else if(dfs(go[u][i])) return 1;
    }
    ins[u]=0;
    return 0;
}

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str);
        insert(str);
    }

    build();
    for(int i=1;i<=rr;i++) cnt[q[i]]|=cnt[fail[q[i]]];
    if(dfs(0)) puts("TAK");
    else puts("NIE");
}

int main()
{
    solve();
    return 0;
}