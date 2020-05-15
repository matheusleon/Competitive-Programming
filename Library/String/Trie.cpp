int trie[MAXN][alpha];
int terminal[MAXN], isLeaf[MAXN];

void insert(string &s) {
    int curr = 0;
    for (int i = 0; i < s.size(); i++) {
        int id = s[i] - 'a';
        if (trie[curr][id] == -1) {
            trie[curr][id] = z++;
        }
        curr = trie[curr][id];
        terminal[curr]++;
    }
    isLeaf[curr]++;
}

bool search(string &s) {
    int curr = 0;
    for (int i = 0; i < s.size(); i++) {
        int id = s[i] - 'a';
        if (terminal[curr] == 0) {
            return false;
        }
        curr = trie[curr][id];
    }
    return isLeaf[curr];
}

void remove(string &s) {
    if (!search(s)) return;
    int curr = 0;
    for (int i = 0; i < s.size(); i++) {
        int id = s[i] - 'a';
        curr = trie[curr][id];
        terminal[curr]--;
    }
    isLeaf[curr]--;
}
