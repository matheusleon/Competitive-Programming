int n;
vector<int> adj[MAXN];
stack<int> stk;
int inStk[MAXN], comp[MAXN], disc[MAXN], low[MAXN];
int timer = 1, sz = 0;

void dfs(int u) {
	stk.push(u);
	inStk[u] = true;
	disc[u] = low[u] = timer++;
	for (int v : adj[u]) {
		if (!disc[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (inStk[v]) {
			low[u] = min(low[u], low[v]);
		}
	}

	if (low[u] == disc[u]) {
		while (stk.top() != u) {
			inStk[stk.top()] = false;
			comp[stk.top()] = sz;
			stk.pop();
		}
		inStk[u] = false;
		comp[stk.top()] = sz;
		stk.pop();
		sz++;
	}
}

void tarjan() {
	for (int i = 0; i < n; i++) {
		if (!disc[i]) dfs(i);
	}
}