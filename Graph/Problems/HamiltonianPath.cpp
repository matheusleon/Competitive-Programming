vector<int> adj[MAXN];
int n;

bool hasHamiltonianPath() {
	vector<vector<bool>> dp(n, vector<bool> ((1 << n)));
	for (int i = 0; i < n; i++) dp[i][(1 << i)] = true;

	for (int mask = 0; mask < (1 << n); mask++) {
		for (int u = 0; u < n; u++) {
			if (mask & (1 << u)) {
				for (int v : adj[u]) {
					if (mask & (1 << v) && dp[v][mask^(1 << u)]) {
						dp[u][mask] = true;
					}
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (dp[i][(1 << n) - 1]) return true;
	}
	return false;
}