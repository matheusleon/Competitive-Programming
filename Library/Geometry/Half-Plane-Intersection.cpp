/*
    Problem: Compute intersection of n convex polygons
    Test: https://www.codechef.com/problems/CHN02
*/

#include <bits/stdc++.h>

using namespace std;

const double inf = 1e100, eps = 1e-9;
const double PI = acos(-1.0L);

int cmp (double a, double b = 0) {
  if (abs(a-b) < eps) return 0;
  return (a < b) ? -1 : +1;
}

struct PT {
  double x, y;
  PT(double x = 0, double y = 0) : x(x), y(y) {}
  PT operator + (const PT &p) const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p) const { return PT(x-p.x, y-p.y); }
  PT operator * (double c) const { return PT(x*c, y*c); }
  PT operator / (double c) const { return PT(x/c, y/c); }
};

double dot (PT p, PT q) { return p.x * q.x + p.y*q.y; }
double cross (PT p, PT q) { return p.x * q.y - p.y*q.x; }


struct L {
    PT a, b;
    L(){}
    L(PT a, PT b) : a(a), b(b) {}
};

double angle (L la) { return atan2(-(la.a.y - la.b.y), la.b.x - la.a.x); }

bool comp (L la, L lb) {       
    if (cmp(angle(la), angle(lb)) == 0) return cross((lb.b - lb.a), (la.b - lb.a)) > eps;
    return cmp(angle(la), angle(lb)) < 0;
}

PT computeLineIntersection (PT a, PT b, PT c, PT d) {
    b = b - a; d = c - d; c = c - a;
    assert(cmp(cross(b, d)) != 0);
    return a + b * cross(c, d) / cross(b, d);
}

PT computeLineIntersection (L la, L lb) {
    return computeLineIntersection(la.a, la.b, lb.a, lb.b);
}

bool check (L la, L lb, L lc) {
    PT p = computeLineIntersection(lb, lc);
    double det = cross((la.b - la.a),  (p - la.a));
    return cmp(det) < 0;
}

vector<PT> hpi (vector<L> line) { // salvar (i, j) CCW, (j, i) CW
    sort(line.begin(), line.end(), comp);
    vector<L> pl(1, line[0]);
    for (int i = 0; i < (int)line.size(); ++i) if (cmp(angle(line[i]), angle(pl.back())) != 0) pl.push_back(line[i]);
    deque<int> dq;
    dq.push_back(0);
    dq.push_back(1);
    for (int i = 2; i < (int)pl.size(); ++i) {
        while ((int)dq.size() > 1 && check(pl[i], pl[dq.back()], pl[dq[dq.size() - 2]])) dq.pop_back();
        while ((int)dq.size() > 1 && check(pl[i], pl[dq[0]], pl[dq[1]])) dq.pop_front();
        dq.push_back(i);
    }
    while ((int)dq.size() > 1 && check(pl[dq[0]], pl[dq.back()], pl[dq[dq.size() - 2]])) dq.pop_back();
    while ((int)dq.size() > 1 && check(pl[dq.back()], pl[dq[0]], pl[dq[1]])) dq.pop_front();
    vector<PT> res;
    for (int i = 0; i < (int)dq.size(); ++i){
        res.emplace_back(computeLineIntersection(pl[dq[i]], pl[dq[(i + 1) % dq.size()]]));
    }
    return res;
}



double computeSignedArea (const vector<PT> &p) {
    double area = 0;
    for (int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area/2.0;
}

double computeArea(const vector<PT> &p) {
    return abs(computeSignedArea(p));
}


int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int m;
    cin >> m;
    vector<L> lines;
    for (int i = 0; i < m; i++) {
        int n;
        cin >> n;
        vector<PT> p(n);
        for (int j = 0; j < n; j++) {
            cin >> p[j].x >> p[j].y;
        }
        for (int j = 0; j < n; j++) {
            lines.push_back(L(p[j], p[(j + 1) % n]));
        }
    }

    vector<PT> pol = hpi(lines);
    cout << fixed << setprecision(4) << computeArea(pol) << '\n';
    return 0;
}