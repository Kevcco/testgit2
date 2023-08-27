/*
题意
给你一个n*m的数字矩阵, n * m <= 1e6
询问能否将矩阵操作成非递减的,
即行内是非递减的,且下一行的第一个不小于上一行的最后一个
可用的操作有:
(1)对于0元素, 可以将其改成任意正整数 (2)交换任意两行 (3)交换任意两列
操作可以使用任意次


首先可以意识到0元素可以直接忽略掉, 因为其他元素排好后, 总能将0赋成合适的值使矩阵非递减
那么就考虑交换操作

(1)先考虑行与行之间, 因为交换列不会影响行间的大小, 因此假设第i行的最大最小值为ma[i],mi[i]
那么必须满足 mi[1] <= ma[1] <= mi[2] <= ma[2] <= ... <= m1[n] <= ma[n]
我们可以处理出来每一行的(mi,ma), 按第一维排序, 检查第二维是否合法即可 
O(n*m + nlogn)

(2)考虑每一行内部需要非递减, 那么对于某一行而言, 就会产生O(m*m)个列之间的相对大小关系
如果第i列需要排到第j列前面, 就从i连边到j, n行处理完之后判断图是否有拓扑序即可
但是这样生成的图是(m, n*m*m)的, 边数 n*m*m = 1e9, 怎么办?

官方题解给出了一个建图trick, 即加中间点
比如值为2的列有{1,2,3,4},值为3的列有{5,6,7,8,9},那么朴素的建图方式就是两两之间都得连,
就是需要连 4 * 5 条边, 但是假如我们添加一个中间节点 u, 
我们将{1,2,3,4}连向u,再将u连向{5,6,7,8,9}, 这样只需要连 4 + 5 条边, 并且不改变想表达的含义
因此按照这种方式建出的图是(n*m, n*m)的, 可以接受 (感觉上是用节点数换边数)
因此建图跑个拓扑排序即可 
O(n*m)

(官方题解还给出了一种数组存n * m矩阵的方法, 即将二维下标映射成一维, 直接存一维数组即可)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e6+10;

int n,m,tot;
pii p[N];
vector<int> e[N*2]; 
int in[N*2],q[N*2],rr;

bool topo()
{
    rr=0;
    for(int i=1;i<tot;i++)
        if(!in[i]) q[++rr]=i;

    for(int i=1;i<=rr;i++)
    {
        int u=q[i];
        for(auto x : e[u])
        {
            in[x]--;
            if(!in[x]) q[++rr]=x;
        }
    }

    return rr==tot-1;
}

void solve()
{
    cin >> n >> m;
    vector<vector<int>> g(n+1,vector<int>(m+1,0));
    for(int i=1;i<=n;i++)
    {
        int ma=-1e9,mi=1e9;
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&g[i][j]);
            if(g[i][j]) ma=max(ma,g[i][j]),mi=min(mi,g[i][j]);
        }
        if(ma>=mi) p[tot++]={mi,ma};
    }

    sort(p,p+tot);

    for(int i=1;i<tot;i++)
    {
        if(p[i].first<p[i-1].second)
        {
            puts("No");
            return;
        }
    }

    tot=m+1;
    for(int i=1;i<=n;i++)
    {
        vector<pii> t;
        for(int j=1;j<=m;j++) if(g[i][j]) t.push_back({g[i][j],j});

        sort(t.begin(),t.end());

        for(int j=1;j<t.size();j++)
        {
            if(t[j].first>t[j-1].first)
            {
                int new_node=tot++;
                int pre=t[j-1].first,nxt=t[j].first;

                for(int k=j-1;k>=0;k--)
                {
                    if(t[k].first!=pre) break;
                    e[t[k].second].push_back(new_node);
                    in[new_node]++;
                }

                for(int k=j;k<t.size();k++)
                {
                    if(t[k].first!=nxt) break;
                    e[new_node].push_back(t[k].second);
                    in[t[k].second]++;
                }
            }
        }
    }

    if(topo()) puts("Yes");
    else puts("No");
}

int main()
{
    solve();
    return 0;
}