/*
    SPOJ - SRTMACH
    Burnside's lemma
*/

#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 98765431;

vector<int> f1, f2;

int fastexp(int x, int y) {
    int ans = 1;
    while (y > 0) {
        if (y & 1) ans = (ans * x) % MOD;
        x = (x * x) % MOD;
        y >>= 1;
    }
    return ans;
}

int countCycles(vector<int> &p) {
    int cycles = 0;
    int n = p.size();
    vector<bool> vis(n);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            cycles++;
            for (int u = i; !vis[u]; u = p[u]) {
                vis[u] = true;
            }
        }
    }
    return cycles;
}

vector<int> apply(vector<int> &p, vector<int> &f) {
    int n = p.size();
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = p[f[i]];
    }
    return ans;
}

set<vector<int>> st;
int n, m;

void go(vector<int> p, int &ans) {
    if (st.count(p)) return;
    st.insert(p);

    int cycles = countCycles(p);
    ans = (ans + fastexp(m, cycles)) % MOD;

    go(apply(p, f1), ans);
    go(apply(p, f2), ans);
}

void solve() {
    st.clear();

    cin >> n >> m;
    f1.resize(n); f2.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> f1[i];
        f1[i]--;
    }
    for (int i = 0; i < n; i++) {
        cin >> f2[i];
        f2[i]--;
    }

    int ans = 0;
    vector<int> v(n);
    for (int i = 0; i < n; i++) v[i] = i;
    go(v, ans);
    
    int inv = fastexp(st.size(), MOD - 2);
    ans = (ans * inv) % MOD;

    cout << ans << '\n';
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}