/*
Assume every vertex of G has degree ≤ x + y + 1 (x, y are given integers).
We wish to color the vertices red or blue (each vertex gets exactly one color) 
such that each red vertex has at most x red neighbors and each blue vertex has at most y blue neighbors.
*/

void solve(int x) {
	queue<int> bad;
	for (int u = 0; u < n; u++) {
		bad.push(u);
	}

	while (!bad.empty()) {
		int u = bad.front();
		bad.pop();

		if (count(u) > x) {
			color[u] = color[u]^1;
			for (int v : adj[u]) {
				bad.push(v);
			}
		}
	}
}