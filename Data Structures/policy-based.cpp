// Calculates the median of each window of k elements

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];

	ordered_set s;
	for (int i = 0; i < k; i++) s.insert(v[i]);

	int mid = (k + 1) / 2 - 1;
	cout << *s.find_by_order(mid) << ' ';
	for (int i = k; i < n; i++) {
		s.erase(s.find_by_order(s.order_of_key(v[i - k])));
		s.insert(v[i]);
		cout << *s.find_by_order(mid) << ' ';
	}
	return 0;
}