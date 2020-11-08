/*
    From: https://github.com/tfg50/Competitive-Programming/blob/master/Biblioteca/Data%20Structures/ColorUpdate.cpp
*/

#include <bits/stdc++.h>

using namespace std;

template <class Info = int, class T = int>
struct ColorUpdate {
public:
    struct Range {
        Range(T _l = 0) : l(_l) {}
        Range(T _l, T _r, Info _v) : l(_l), r(_r), v(_v) { }
        T l, r;
        Info v;

        bool operator < (const Range &b) const { return l < b.l; }
    };

    std::vector<Range> erase(T l, T r) {
        std::vector<Range> ans;
        if(l >= r) return ans;
        auto it = ranges.lower_bound(l);
        if(it != ranges.begin()) {
            it--;
            if(it->r > l) {
                auto cur = *it;
                ranges.erase(it);
                ranges.insert(Range(cur.l, l, cur.v));
                ranges.insert(Range(l, cur.r, cur.v));
            }
        }
        it = ranges.lower_bound(r);
        if(it != ranges.begin()) {
            it--;
            if(it->r > r) {
                auto cur = *it;
                ranges.erase(it);
                ranges.insert(Range(cur.l, r, cur.v));
                ranges.insert(Range(r, cur.r, cur.v));
            }
        }
        for(it = ranges.lower_bound(l); it != ranges.end() && it->l < r; it++) {
            ans.push_back(*it);
        }
        ranges.erase(ranges.lower_bound(l), ranges.lower_bound(r));
        return ans;
    }

    std::vector<Range> upd(T l, T r, Info v) {  // updates [l, r)
        auto ans = erase(l, r);
        ranges.insert(Range(l, r, v));
        return ans;
    }

    bool exists(T x) {
        auto it = ranges.upper_bound(x);
        if(it == ranges.begin()) return false;
        it--;
        return it->l <= x && x < it->r;
    }
    std::set<Range> ranges;
};


int32_t main() {
    //ios::sync_with_stdio(0); cin.tie(0);
    int n, q;
    cin >> n >> q;
    ColorUpdate<int, int> st;
    for (int i = 0; i < q; i++) {
        int l, r, c;
        scanf("%d %d %d", &l, &r, &c);
        st.upd(l, r + 1, c);
    }

    vector<int> ans(n + 1);
    for (auto interval : st.ranges) {
        for (int i = interval.l; i <= interval.r; i++) {
            ans[i] = interval.v;
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}