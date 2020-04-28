// UNDIRECTED GRAPH

int n;
set<int> adj[MAXN];
int deg[MAXN], vis[MAXN];

void isConnected(int u) {
	vis[u] = true;
	for (int v : adj[u]) if (!vis[v]) isConnected(v);
}

bool isEulerian() {
	isConnected(0);
	for (int i = 0; i < n; i++) {
		if (!vis[i] && adj[i].size()) return false;
		if (deg[i] % 2 != 0) return false;
	}
	return true;
}

void dfs(int u, vector<int> &euler) {
	while (adj[u].size()) {
		int v = *adj[u].begin();
		adj[u].erase(v);
		adj[v].erase(u);
		dfs(v, euler);
	}
	euler.push_back(u);
}

vector<int> eulerCircuit() {
	vector<int> euler;
	dfs(0, euler);
	//reverse(euler.begin(), euler.end());
	return euler;
}




// DIRECTED GRAPH

int n;
vector<int> adj[MAXN];
int in[MAXN], out[MAXN];
int curr_edge[MAXN];

int hasEulerianPath() {
	int u = -1, v = -1;
	for (int i = 0; i < n; i++) {
		if (in[i] - out[i] == 0) continue;
		if (out[i] - in[i] == 1) {
			if (u == -1) u = i;
			else return -1;
		} else if (in[i] - out[i] == 1) {
			if (v == -1) v = i;
			else return -1;
		} else {
			return -1;
		}
	}
	if (u == -1) u = 0;
	return u;
}

vector<int> eulerPath(int u) {
	vector<int> ans;
	stack<int> stk;
	stk.push(u);
	while (!stk.empty()) {
		int u = stk.top();
		stk.pop();
		while (curr_edge[u] < (int)adj[u].size()) {
			stk.push(u);
			u = adj[u][curr_edge[u]++];
		}
		ans.push_back(u);
	}
	reverse(ans.begin(), ans.end());
	return ans;
}