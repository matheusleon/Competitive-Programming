typedef pair<int, int> pii;
 
int p[MAXN];
vector<pii> adj[MAXN];
int dist[MAXN];
bool hasNegativeCycle = false;
int n;
 
void bellmanford(int s) {
	int start = -1;
	for (int i = 0; i < MAXN; i++) dist[i] = INF;
	dist[s] = 0;
	for (int i = 0; i < n; i++) {
		for (int u = 0; u < n; u++) {
			for (auto e : adj[u]) {
				int v = e.first, w = e.second;
				if (i == n - 1 && dist[v] > dist[u] + w) {
					hasNegativeCycle = true;
					p[v] = u;
					start = v;
				} else {
					if (dist[v] > dist[u] + w) {
						dist[v] = dist[u] + w;
						p[v] = u; 
					}
				}
			}
		}
	}

	if (hasNegativeCycle) {
		cout << "YES\n";

		for (int i = 0; i < n; i++) start = p[start];

		vector<int> path;
		path.push_back(start);
		for (int u = p[start]; u != start; u = p[u]) {
			path.push_back(u);
		}
		reverse(path.begin(), path.end());
		path.push_back(path[0]);

		for (int x : path) cout << x + 1 << ' ';
		cout << '\n';
	} else {
		cout << "NO\n";
	}
}