struct UnionFind {

  int n, group_numbers;
  vector<int> parents;
  vector<vector<int>> G;

  UnionFind(int n_) {
    n = n_;
    parents.resize(n, -1);
    G.resize(n);
    group_numbers = n;
  }

  int root(int x) {
    int a = x, y;
    while (parents[a] >= 0) {
      a = parents[a];
    }
    while (parents[x] >= 0) {
      y = x;
      x = parents[x];
      parents[y] = a;
    }
    return a;
  }

  bool unite(int x, int y) {
    x = root(x);
    y = root(y);
    if (x == y) return false;
    --group_numbers;
    G[x].emplace_back(y);
    G[y].emplace_back(x);
    if (parents[x] >= parents[y]) swap(x, y);
    parents[x] += parents[y];
    parents[y] = x;
    return true;
  }

  int size(const int x) {
    return -parents[root(x)];
  }

  bool same(const int x, const int y) {
    return root(x) == root(y);
  }

  set<int> members(int x) {
    set<int> seen;
    seen.insert(x);
    vector<int> todo = {x};
    while (!todo.empty()) {
      int v = todo.back(); todo.pop_back();
      for (int &x: G[v]) {
        if (seen.count(x)) continue;
        todo.emplace_back(x);
        seen.insert(x);
      }
    }
    return seen;
  }

  vector<int> all_roots() {
    vector<int> res;
    for (int i = 0; i < n; ++i) {
      if (parents[i] < 0) res.emplace_back(i);
    }
    return res;
  }

  int group_count() {
    return group_numbers;
  }

  void clear() {
    group_numbers = n;
    for (int i = 0; i < n; ++i) parents[i] = -1;
  }

  map<int, vector<int>> all_group_members() {
    map<int, vector<int>> res;
    for (int i = 0; i < n; ++i) res[root(i)].emplace_back(i);
    return res;
  }

  void print() {
    map<int, vector<int>> group_members = all_group_members();
    printf("<UnionFind>\n");
    for (auto &[key, val]: group_members) {
      printf(" %d:", key);
      for (int &v: val) {
        printf(" %d", v);
      }
      cout << endl;
    }
  }
};

