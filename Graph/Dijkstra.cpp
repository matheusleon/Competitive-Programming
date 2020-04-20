typedef pair<int, int> pii;

vector<pii> adj[MAXN];
int dist[MAXN];

void dijkstra(int s) {
	for (int i = 0; i < MAXN; i++) dist[i] = INF;
	dist[s] = 0;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({dist[s], s});
	while (!pq.empty()) {
		int u = pq.top().second, d = pq.top().first;
		pq.pop();
		if (dist[u] < d) continue;
		for (pii e : adj[u]) {
			int v = e.first, w = e.second;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pq.push({dist[v], v});
			}
		}
	}
}