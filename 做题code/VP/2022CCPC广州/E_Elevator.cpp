#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mn = 500005;
map<int, int> order;
vector<int> lis;
int x[mn];
int sum[mn], num[mn], n;
ll global[mn];
void update(int p, int d) {
    for(int i = p; i <= n; i += i & -i) {
        num[i] += d;
    }
}
int getsum(int p) {
    int ret = 0;
    for(int i = p; i; i -= i & -i) {
        ret += num[i];
    }
    return ret;
}
int main() {
    int m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &x[i]);
        lis.push_back(x[i]);
    }
    sort(lis.begin(), lis.end());
    lis.erase(unique(lis.begin(), lis.end()), lis.end());
    for(int i = 0; i < lis.size(); i++) {
        order[lis[i]] = i + 1;
    }
    for(int i = 1; i <= n; i++) {
        ++sum[order[x[i]]];
        global[order[x[i]]] += x[i];
    }
    for(int i = 1; i <= lis.size(); i++) {
        sum[i] += sum[i - 1];
        global[i] += global[i - 1];
    }
    for(int i = 1; i <= n; i++) {
        ll tmp = 1ll * sum[order[x[i]] - 1] * x[i] - global[order[x[i]] - 1] + getsum(order[x[i]]);
        if(tmp > m - 2) {
            puts("-1");
        } else {
            printf("%lld\n", tmp);
        }
        update(order[x[i]], 1);
    }
}