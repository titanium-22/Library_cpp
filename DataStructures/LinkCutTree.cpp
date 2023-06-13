template<typename T>
struct LinkCutTree {

  int n, group_cnt;
  vector<int> arr, size;
  vector<T> key, data;
  function<T (T, T)> _op;
  T _e;

  LinkCutTree(int _n, function<T (T, T)> op, T e) {
    n = _n;
    _op = op;
    _e = e;
    key.resize(n+1, e);
    data.resize(2*n+2, e);
    arr.resize(4*n+4, n);
    for (int i = 3; i < 4*n+4; i+=4) {
      arr[i] = 0;
    }
    size.resize(n+1, 1);
    size[n] = 0;
  }

  bool _is_root(int node) {
    if (arr[node<<2|2] == n) {
      return true;
    }
    if ((arr[arr[node<<2|2]<<2] == node) || (arr[arr[node<<2|2]<<2|1] == node)) {
      return false;
    }
    return true;
  }

  void _propagate(int node) {
    if (node == n) return;
    if (arr[node<<2|3]) {
      arr[node<<2|3] = 0;
      swap(data[node<<1], data[node<<1|1]);
      int ln = arr[node<<2], rn = arr[node<<2|1];
      arr[node<<2] = rn;
      arr[node<<2|1] = ln;
      arr[ln<<2|3] ^= 1;
      arr[rn<<2|3] ^= 1;
    }
    // 遅延評価はあとで
  }

  void _update(int node) {
    if (node == n) return;
    int ln = arr[node<<2], rn =  arr[node<<2|1];
    _propagate(ln);
    _propagate(rn);
    data[node<<1] = _op(_op(data[ln<<1], key[node]), data[rn<<1]);
    data[node<<1|1] = _op(_op(data[rn<<1|1], key[node]), data[ln<<1|1]);
    size[node] = 1 + size[ln] + size[rn];
  }

  void _update_triple(int x, int y, int z) {
    int lx = arr[x<<2], rx = arr[x<<2|1];
    int ly = arr[y<<2], ry = arr[y<<2|1];
    _propagate(lx);
    _propagate(rx);
    _propagate(ly);
    _propagate(ry);
    data[z<<1] = data[x<<1];
    data[x<<1] = _op(_op(data[lx<<1], key[x]), data[rx<<1]);
    data[y<<1] = _op(_op(data[ly<<1], key[y]), data[ry<<1]);
    data[z<<1|1] = data[x<<1|1];
    data[x<<1|1] = _op(_op(data[rx<<1|1], key[x]), data[lx<<1|1]);
    data[y<<1|1] = _op(_op(data[ry<<1|1], key[y]), data[ly<<1|1]);
    size[z] = size[x];
    size[x] = 1 + size[lx] + size[rx];
    size[y] = 1 + size[ly] + size[ry];
  }

  void _update_double(int x, int y) {
    int lx = arr[x<<2], rx = arr[x<<2|1];
    _propagate(lx);
    _propagate(rx);
    data[y<<1] = data[x<<1];
    data[x<<1] = _op(_op(data[lx<<1], key[x]), data[rx<<1]);
    data[y<<1|1] = data[x<<1|1];
    data[x<<1|1] = _op(_op(data[rx<<1|1], key[x]), data[lx<<1|1]);
    size[y] = size[x];
    size[x] = 1 + size[lx] + size[rx];
  }

  void _splay(int node) {
    if (node == n) return;
    _propagate(node);
    if (_is_root(node)) return;
    int pnode = arr[node<<2|2], gnode, nnode, f, g;
    while (!_is_root(pnode)) {
      gnode = arr[pnode<<2|2];
      _propagate(gnode);
      _propagate(pnode);
      _propagate(node);
      f = arr[pnode<<2] == node;
      g = (arr[gnode<<2|f] == pnode) ^ (arr[pnode<<2|f] == node);
      nnode = (g? node : pnode) << 2 | f ^ g;
      arr[pnode<<2|f^1] = arr[node<<2|f];
      arr[gnode<<2|f^g^1] = arr[nnode];
      arr[node<<2|f] = pnode;
      arr[nnode] = gnode;
      arr[node<<2|2] = arr[gnode<<2|2];
      arr[gnode<<2|2] = nnode>>2;
      arr[arr[pnode<<2|f^1]<<2|2] = pnode;
      arr[arr[gnode<<2|f^g^1]<<2|2] = gnode;
      arr[pnode<<2|2] = node;
      _update_triple(gnode, pnode, node);
      pnode = arr[node<<2|2];
      if (arr[pnode<<2] == gnode) {
        arr[pnode<<2] = node;
      } else if (arr[pnode<<2|1] == gnode) {
        arr[pnode<<2|1] = node;
      } else {
        return;
      }
    }
    _propagate(pnode);
    _propagate(node);
    f = arr[pnode<<2] == node;
    arr[pnode<<2|f^1] = arr[node<<2|f];
    arr[node<<2|f] = pnode;
    arr[arr[pnode<<2|f^1]<<2|2] = pnode;
    arr[node<<2|2] = arr[pnode<<2|2];
    arr[pnode<<2|2] = node;
    _update_double(pnode, node);
  }

  int expose(int v) {
    int pre = v;
    while (arr[v<<2|2] != n) {
      _splay(v);
      arr[v<<2|1] = n;
      _update(v);
      if (arr[v<<2|2] == n) break;
      pre = arr[v<<2|2];
      _splay(pre);
      arr[pre<<2|1] = v;
      _update(pre);
    }
    arr[v<<2|1] = n;
    _update(v);
    return pre;
  }

  int lca(int root, int u, int v) {
    evert(root);
    expose(u);
    return expose(v);
  }

  void link(int c, int p) {
    // assert(!same(c, p))
    expose(c);
    expose(p);
    arr[c<<2|2] = p;
    arr[p<<2|1] = c;
    _update(p);
    --group_cnt;
  }

  void cut(int c) {
    expose(c);
    // assert arr[c<<2] != n;
    arr[arr[c<<2]<<2|2] = n;
    arr[c<<2] = n;
    _update(c);
    ++group_cnt;
  }

  int group_count() {
    return group_cnt;
  }

  int root(int v) {
    expose(v);
    while (arr[v<<2] != n) {
      v = arr[v<<2];
      _propagate(v);
    }
    _splay(v);
    return v;
  }

  bool same(int u, int v) {
    return root(u) == root(v);
  }

  void evert(int v) {
    expose(v);
    arr[v<<2|3] ^= 1;
    _propagate(v);
  }

  T prod(int u, int v) {
    evert(u);
    expose(v);
    return data[v<<1];
  }

  int path_length(int u, int v) {
    evert(u);
    expose(v);
    return size[v];
  }

  bool merge(int u, int v) {
    if (same(u, v)) return false;
    evert(u);
    expose(v);
    arr[u<<2|2] = v;
    arr[v<<2|1] = u;
    _update(v);
    return true;
  }

  bool split(int u, int v) {
    if (!same(v, u)) return false;
    evert(u);
    cut(v);
    return true;
  }

  int path_kth_elm(int s, int t, int k) {
    evert(s);
    expose(t);
    if (size[t] <= k) return -1;
    while (1) {
      _propagate(t);
      s = size[arr[t<<2]];
      if (s == k) {
        _splay(t);
        return t;
      }
      t = arr[t<<2|(s<k)];
      if (s < k) {
        k -= s + 1;
      }
    }
  }

  T get(int k) {
    _splay(k);
    return key[k];
  }

  void set(int k, T v) {
    _splay(k);
    key[k] = v;
    _update(k);
  }
};
