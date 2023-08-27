#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e6+10;

int n,m,k;
int trie[N][26],fail[N],go[N][26],idx;
char s[N],str[N];
int cnt[N],res[N];
int q[N],rr;

void insert(int u)
{
    int len=strlen(str+1);
    int p=0;
    for(int i=1;i<=len;i++)
    {
        int t=str[i]-'a';
        if(!trie[p][t]) trie[p][t]=++idx;
        p=trie[p][t];
    }
    res[u]=p;
}

void build()
{
    rr=-1;
    q[++rr]=0;
    for(int i=0;i<=rr;i++)
    {
        int t=q[i];
        for(int j=0;j<26;j++)
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

void query()
{
    int p=0;
    int len=strlen(s+1);
    for(int i=1;i<=len;i++)
    {
        int t=s[i]-'a';
        p=go[p][t];
        cnt[p]++;
    }
}

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+1);
        insert(i);
    }
    scanf("%s",s+1);
    build();
    query();
    for(int i=rr;i>0;i--) cnt[fail[q[i]]]+=cnt[q[i]];
    for(int i=1;i<=n;i++) printf("%d\n",cnt[res[i]]);
}

int main()
{
    solve();
    return 0;
}