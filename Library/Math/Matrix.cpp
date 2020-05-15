typedef long long ll;

struct Matrix {
    int n;
    ll mod;
    vector<vector<ll>> mat;
    
    Matrix(int n, ll mod) : n(n), mod(mod) {
        mat.resize(n, vector<ll> (n));
    }

    Matrix operator * (const Matrix &b) {
        Matrix c(n, mod);
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
                for (int k = 0; k < n; k++) 
                    c.mat[i][j] = (c.mat[i][j] + mat[i][k] * b.mat[k][j]) % mod;
        return c;
    }
};

Matrix pow(Matrix a, ll p) {
    Matrix ans(a.n, a.mod);
    for (int i = 0; i < a.n; i++)
        for (int j = 0; j < a.n; j++)
            ans.mat[i][j] = (i == j);

    while(p) {
        if (p & 1) ans = ans * a;
        a = a * a;
        p = p >> 1;
    }
    return ans;
} 