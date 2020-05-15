#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 1e5 + 7;

set<pii> st[MAXN];
int n;

bool isSmaller(const pii &a, const pii &b) {
    return a.first < b.first && a.second < b.second;
}

bool check(pii a, int id) {
    for (pii b : st[id]) {
        if (isSmaller(b, a)) return true;
    }
    return false;
}

int search(pii a) {
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (check(a, m)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    vector<pii> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }
    
    int sz = 0;
    for (int i = 0; i < n; i++) {
        int x = v[i].first, y = v[i].second;
        int id = search(v[i]);
        sz = max(sz, id + 1);
        
        auto it = st[id].insert(v[i]).first;
        it++;
        while (it != st[id].end()) {
            if (isSmaller(v[i], *it)) st[id].erase(it++);
            else it++;
        }
    }
    cout << sz << '\n';
    return 0;
}