template<typename T>
struct SegmentTree {
  int _n, _size, _log;
  vector<T> _data;
  function<T (T, T)> _op;
  T _e;

  SegmentTree(int n, function<T (T, T)> op, T e) {
    _op = op;
    _e = e;
    _n = n;
    _log = 32 - __builtin_clz(_n-1);
    _size = 1 << _log;
    _data.resize(_size << 1, _e);
  }

  SegmentTree(vector<T> a, function<T (T, T)> op, T e) {
    _n = (int)a.size();
    SegmentTree(_n, op, e);
    for (int i = 0; i < _n; ++i) {
      _data[i+_size] = a[i];
    }
    for (int i = _size-1; i > 0; --i) {
      _data[i] = _op(_data[i<<1], _data[i<<1|1]);
    }
  }

  T get(int k) {
    if (k < 0) k += _n;
    return _data[k+_size];
  }

  void set(int k, T v) {
    if (k < 0) k += _n;
    k += _size;
    _data[k] = v;
    for (int i = 0; i < _log; ++i) {
      k >>= 1;
      _data[k] = _op(_data[k<<1], _data[k<<1|1]);
    }
  }

  T prod(int l, int r) {
    l += _size;
    r += _size;
    T lres = _e, rres = _e;
    while (l < r) {
      if (l & 1) {
        lres = _op(lres, _data[l++]);
      }
      if (r & 1) {
        rres = _op(_data[r^1], rres);
      }
      l >>= 1;
      r >>= 1;
    }
    return _op(lres, rres);
  }

  T all_prod() {
    return _data[1];
  }

  int max_right(int l, function<bool (T)> f) {
    if (l == _n) return _n;
    l += _size;
    T s = _e;
    while (1) {
      while (l & 1 == 0) {
        l >>= 1;
      }
      if (!f(_op(s, _data[l]))) {
        while (l < _size) {
          l <<= 1;
          if (f(_op(s, _data[l]))) {
            s = _op(s, _data[l]);
            l |= 1;
          }
        }
        return l - _size;
      }
      s = _op(s, _data[l]);
      ++l;
      if (l & (-l) == l) break;
    }
    return _n;
  }

  int min_left(int r, function<bool (T)> f) {
    if (r == 0) return 0;
    r += _size;
    T s = _e;
    while (1) {
      --r;
      while (r > 1 && (r & 1)) {
        r >>= 1;
      }
      if (!f(_op(data[r], s))) {
        while (r < _size) {
          r = r << 1 | 1;
          if (f(_op(_data[r], s))) {
            s = _op(_data[r], s);
            r ^= 1;
          }
        }
        return r + 1 - _size;
      }
      s = _op(_data[r], s);
      if (r & (-r) == r) break;
    }
    return 0;
  }

  vector<T> tovector() {
    vector<T> res(_n);
    for (int i = 0; i < _n; ++i) {
      res[i] = get(i);
    }
    return res;
  }

  void print() {
    return;
  }
};
