// Find the shortest cycle that uses each edge at least once

#include <bits/stdc++.h>

using namespace std;

const int MAXN = (1 << 15);
const int INF = 1e9;

int dp[MAXN];
int deg[15], dist[15][15];
vector<int> odd;

int solve(int mask) {
    if (mask == 0) return 0;
    int &ans = dp[mask];
    if (~ans) return ans;
    ans = INF;
    for (int i = 0; i < odd.size(); i++) {
        for (int j = 0; j < odd.size(); j++) {
            if (i == j) continue;
            if ((mask & (1 << i)) > 0 && (mask & (1 << j)) > 0) {
                ans = min(ans, dist[odd[i]][odd[j]] + solve(mask ^ (1 << i) ^ (1 << j)));
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m;
    while (cin >> n >> m, n) {
        for (int i = 0; i < n; i++) {
            deg[i] = 0;
            for (int j = 0; j < n; j++) {
                if (i == j) dist[i][j] = 0;
                else dist[i][j] = INF;
            }
        }
        odd.clear();

        int total = 0;
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--; v--;
            dist[u][v] = min(dist[u][v], w);
            dist[v][u] = min(dist[v][u], w);
            deg[u]++; deg[v]++;

            total += w;
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (deg[i] % 2 == 1) {
                odd.push_back(i);
            }
        }

        memset(dp, -1, sizeof dp);
        cout << total + solve((1 << odd.size()) - 1) << '\n';
    }
    return 0;
}