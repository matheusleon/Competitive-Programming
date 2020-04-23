vector<int> sccs[MAXN];
vector<int> adj[MAXN], radj[MAXN];
int vis[MAXN];
stack<int> stk;
int n;

void dfs(int u) {
	vis[u] = true;
	for (int v : adj[u]) {
		if (!vis[v]) dfs(v);
	}
	stk.push(u);
}

void dfs2(int u, int curr) {
	vis[u] = true;
	sccs[curr].push_back(u);
	for (int v : radj[u]) {
		if (!vis[v]) dfs2(v, curr);
	}
}

void kosaraju() {
	for (int i = 0; i < n; i++) {
		if (!vis[i]) dfs(i);
	}
	memset(vis, false, sizeof(vis));

	int curr = 0;
	while (!stk.empty()) {
		int x = stk.top();
		stk.pop();
		if (!vis[x]) {
			dfs2(x, curr);
			curr++;
		}
	}
	
	for (int i = 0; i < curr; i++) {
		for (int x : sccs[i]) {
			cout << x << ' ';
		}
		cout << '\n';
	}
}
