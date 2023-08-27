// https://ac.nowcoder.com/acm/contest/29086/I
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e6+10,M=26;

int n,m,idx;
int trie[N][M],go[N][M],fail[N],cnt[N];
int trie2[N][M],cnt2[N],idx2,pos2[N];
int q[N],rr,res[N];
char s[N];

void insert(char *s,int pos)
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
    res[pos]=p;
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

void query(int p,int q)
{
    for(int i=0;i<26;i++)
    {
        if(trie2[p][i])
        {
            cnt[go[q][i]]++;
            query(trie2[p][i],go[q][i]);
        }
    }
}

void solve()
{
    cin >> n >> m;
    int p=0;
    for(int i=1;i<=n;i++)
    {
        char op[2];
        int last;
        scanf("%s%d",op,&last);
        p=pos2[last];
        int t=op[0]-'A';
        if(!trie2[p][t]) trie2[p][t]=++idx2;
        p=trie2[p][t];
        pos2[i]=p;
        cnt2[p]++;
    }

    for(int i=1;i<=m;i++)
    {
        scanf("%s",s);
        int len=strlen(s);
        reverse(s,s+len);
        insert(s,i);
    }
    build();
    query(0,0);

    for(int i=rr;i>0;i--) cnt[fail[q[i]]]+=cnt[q[i]];
    for(int i=1;i<=m;i++) printf("%d\n",cnt[res[i]]);

}

int main()
{
    solve();
    return 0;
}