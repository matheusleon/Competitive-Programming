typedef long long ll;
typedef long double ld;

struct line {
	ll k, b, idx;
	line() {}
	line(ll k, ll b, ll idx = 0) : k(k), b(b), idx(idx) {}
	bool operator <(const line & l) const {
		if (k != l.k) return k < l.k;
		return b < l.b;
	}
};
 
struct ConvexHullTrick {
    vector<line> v;
    ConvexHullTrick() {}

    void addOffline(line l) {
        v.push_back(l);
    }

    static ld intersectPoint(line a, line b) {
        return ld(b.b - a.b) / (a.k - b.k);
    }

    static bool isBad(line a, line b, line c) {
        return intersectPoint(a, b) >= intersectPoint(b, c);
    }

    void addOnline(line l) {
        while ((v.size() >= 1 && v.back().k == l.k && v.back().b <= l.b) || 
                (v.size() >= 2 && isBad(v[(int)v.size() - 2], v.back(), l))) v.pop_back();
        v.push_back(l);
    }

    void process() {
        vector<line> tmp = v;
        v.resize(0);
        sort(tmp.begin(), tmp.end());
        for (auto p : tmp) {
            addOnline(p);
        }
    }

    static ll get(line l, ll x) {
        return x * l.k + l.b;
    }

    // return (max(k*x + b), idx)
    pair<ll, int> query(ll x) {
        if (v.empty()) return {numeric_limits<ll>::min(), 0};
        int l = -1, r = (int)v.size() - 1;
        while (r - l > 1) {
            int mid = (l + r) >> 1;
            if (get(v[mid], x) <= get(v[mid + 1], x)) l = mid;
            else r = mid;
        }
        return {get(v[r], x), v[r].idx};
    }
};
