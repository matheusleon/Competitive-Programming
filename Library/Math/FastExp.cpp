int fastexp(int x, int y, int MOD) {
	int ans = 1;
	while (y > 0) {
		if (y & 1) ans = (ans * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return ans;
}