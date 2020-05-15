vector<int> edges;
unordered_set<string> vis;

void dfs(string u, int k, string &s) {
	for (int i = 0; i < k; i++) {
		string v = u + s[i];
		if (!vis.count(v)) {
			vis.insert(v);
			dfs(v.substr(1), k, s);
			edges.push_back(i);
		}
	}
}

string deBrujin(int n, int k, string &alphabet) {
	string start = string(n - 1, alphabet[0]);
	dfs(start, k, alphabet);
	int len = pow(k, n);
	string ans;
	for (int i = 0; i < len; i++) {
		ans += alphabet[edges[i]];
	}
	ans += start;
	return ans;
}