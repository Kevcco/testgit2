#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mn = 2005;
ll f[mn][mn][2], minp[mn], parent[mn], h[mn][2], maxs[mn], to[mn];
int num[mn];
int a[mn], t[mn];
vector<int> g[mn];
void dfs(int u, int fa) {
    bool leaf = 1;
    parent[u] = fa;
    for(auto v : g[u]) {
        if(v != fa) {
            dfs(v, u);
            num[u] += num[v];
            leaf = 0;
        }
    }
    num[u] += leaf;
}
void dp(int u) {
    bool leaf = 1;
    for(auto v : g[u]) {
        if(v != parent[u]) {
            dp(v);
            leaf = 0;
        }
    }
    if(leaf) {
        f[u][0][0] = 0;
        f[u][0][1] = a[u];
        f[u][1][0] = t[1];
        f[u][1][1] = a[u] + t[1];
        return;
    }
    for(int i = 0; i <= num[u]; i++) {
        f[u][i][1] = a[u] + t[i];
        f[u][i][0] = t[i];
        maxs[i] = 0;
    }
    // if(u == 1) {
    //     for(int i = 0; i <= num[u]; i++) {
    //         printf("%lld %lld\n", f[1][i][0], f[1][i][1]);
    //     }
    // }
    for(auto v : g[u]) {
        int sum = 0;
        if(v != parent[u]) {
            sum += num[v];
            for(int i = 0; i <= sum; i++) {
                h[i][1] = 1ll << 59;
                h[i][0] = 1ll << 59;
                for(int j = 0; j <= num[v] && j <= i; j++) {
                    h[i][1] = min(h[i][1], f[u][i - j][1] - t[i - j] + min(f[to[v]][j][1], f[to[v]][j][0]) - t[j] + t[i]);
                    h[i][0] = min(h[i][0], f[u][i - j][0] - t[i - j] + min(minp[v] + f[to[v]][j][0], f[to[v]][j][1]) - t[j] + t[i]);
                    if(h[i][0] == f[u][i - j][0] - t[i - j] + minp[v] + f[to[v]][j][0] - t[j] + t[i]) {
                        maxs[i] = max(maxs[i], minp[v]);
                    }
                }
            }
            if(u == 1) {
                for(int i = 0; i <= num[u]; i++) {
                    printf("%lld %lld\n", h[i][0], h[i][1]);
                }
            }
            for(int i = 0; i <= num[u]; i++) {
                f[u][i][1] = h[i][1];
                f[u][i][0] = h[i][0];
            }
        }
        puts("---");
    }
    for(int i = 0; i <= num[u]; i++) {
        f[u][i][0] -= maxs[i];
    }
}
int main() {
    int T, n, u, v;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            g[i].clear();
            minp[i] = 1ll << 59;
            to[i] = num[i] = 0;
            memset(f[i], 0x3f, sizeof f[i]);
        }
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        for(int i = 1; i <= n; i++) {
            scanf("%d", &t[i]);
        }
        for(int i = 1; i < n; i++) {
            scanf("%d%d", &u, &v);
            g[u].push_back(v), g[v].push_back(u);
        }
        dfs(1, 0);
        for(int i = 1; i <= n; i++) {
            int u = i;
            while(g[u].size() - (parent[u] > 0) == 1) {
                int v1 = g[u][0], v2 = g[u][1];
                if(parent[u] == v1) {
                    swap(v1, v2);
                }
                minp[i] = min(minp[i], 1ll * a[u]);
                u = v1;
            }
            if(g[u].size() - (parent[u] > 0) == 0) {
                minp[i] = min(minp[i], 1ll * a[u]);
                to[i] = 0;
            } else {
                to[i] = u;
            }
            // printf("%d:%d %lld\n\n", i, to[i], minp[i]);
        }
        // printf("%d\n", to[1]);
        for(int i = 0; i <= n; i++) {
            f[0][i][0] = f[0][i][1] = 1ll << 59;
        }
        f[0][0][0] = 0;
        dp(1);
        // for(int i = 0; i <= n; i++) {
        //     printf("%lld\n", f[1][i][0]);
        // }
        ll ans = 1ll << 62;
        for(int i = 0; i <= n; i++) {
            ans = min(ans, min(f[1][i][1], f[1][i][0]));
            // printf("%lld\n", ans);
        }
        // printf("%lld\n", minp[2]);
        printf("%lld\n", ans);
    }
}
