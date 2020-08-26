struct Node {
    Node *left, *right;

    Node(int c) {
        left = right = nullptr;
    }

    Node(Node *l, Node *r) : left(l), right(r) {

    }
};

Node* build(int l, int r, vector<int> &v) {
    if (l == r) {
        return new Node(v[l]);
    }
    int m = (l + r) >> 1;
    return new Node(build(l, m, v), build(m + 1, r, v));
}

Node *update(Node *on, int l, int r, int pos, int val) {
    if (l == r) {
        return new Node(val);
    }
    int m = (l + r) >> 1;
    if (pos <= m) {
        return new Node(update(on->left, l, m, pos, val), on->right);
    } else {
        return new Node(on->left, update(on->right, m + 1, r, pos, val));
    }
}

Node *query(Node *on, int l, int r, int pos) {
    if (l == r) {
        return on;
    }
    int m = (l + r) >> 1;
    if (pos <= m) {
        return query(on->left, l, m, pos);
    } else {
        return query(on->right, m + 1, r, pos);
    }
}