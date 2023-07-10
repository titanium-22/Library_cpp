template<typename T>
struct SortedSet {

  static constexpr int BUCKET_RATIO = 50;
  static constexpr int REBUILD_RATIO = 170;
  vector<vector<T>> _a;
  int _n;

  SortedSet() {
    _n = 0;
  }

  SortedSet(vector<T> a) {
    _n = (int)a.size();
    vector<T> aa = a;
    for (int i = 0; i < _n-1; ++i) {
      if (!(aa[i] < aa[i+1])) {
        sort(aa.begin(), aa.end());
        aa.erase(unique(aa.begin(), aa.end()), aa.end());
        break;
      }
    }
    _build(aa);
  }

  void _build(const vector<T> &a) {
    int n = a.size();
    this->_n = n;
    int bucket_size = ceil(sqrt(n / (double)BUCKET_RATIO));
    this->_a.clear();
    this->_a.resize(bucket_size);
    for (int i = 0; i < bucket_size; ++i) {
      int start = (long long)n * i / bucket_size;
      int stop = min((long long)n * (i+1) / bucket_size, (long long)a.size());
      _a[i].reserve(stop - start);
      for (int j = start; j < stop; ++j) {
        _a[i].emplace_back(a[j]);
      }
    }
  }

  void _rebuild() {
    vector<T> a;
    for (const auto &aa: _a) a.insert(a.end(), aa.begin(), aa.end());
    _build(a);
  }

  int _bisect_left(const vector<T> &a, T x) {
    int ng = 0, ok = a.size();
    while (ok - ng > 1) {
      int mid = (ng + ok) >> 1;
      (a[mid] < x? ng: ok) = mid;
    }
    return ok;
  }

  int _bisect_right(const vector<T> &a, T x) {
    int left = 0, right = a.size();
    while (left < right) {
      int mid = (left + right) >> 1;
      if (x < a[mid]) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }

  pair<int, int> _positiion(const T x) {
    int i;
    for (i = 0; i < _a.size()-1; ++i) {
      if (x <= _a[i].back()) break;
    }
    return {i, _bisect_left(_a[i], x)};
  }

  bool contains(const T x) {
    if (_n == 0) return false;
    int a_i, i;
    tie(a_i, i) = _positiion(x);
    return (i != (int)_a[a_i].size() && _a[a_i][i] == x);
  }

  bool add(const T x) {
    if (_n == 0) {
      _a.resize(1);
      _a[0].emplace_back(x);
      ++_n;
      return true;
    }
    int a_i, i;
    tie(a_i, i) = _positiion(x);
    if (i != (int)_a[a_i].size() && _a[a_i][i] == x) return false;
    _a[a_i].insert(_a[a_i].begin() + i, x);
    ++_n;
    if ((int)_a[a_i].size() > (long long)_a.size() * REBUILD_RATIO) _rebuild();
    return true;
  }

  T _pop(vector<T> &a, int i) {
    T x = a[i];
    a.erase(a.begin() + i);
    --_n;
    if (a.empty()) _rebuild();
    return x;
  }

  bool discard(const T x) {
    if (_n == 0) return false;
    int a_i, i;
    tie(a_i, i) = _positiion(x);
    if (i == (int)_a[a_i].size() || _a[a_i][i] != x) return false;
    _pop(_a[a_i], i);
    return true;
  }

  optional<T> lt(const T x) {
    optional<T> res = nullopt;
    for_each(_a.rbegin(), _a.rend(), [&](const auto& a) {
      if (a[0] < x) {
        res = a[_bisect_left(a, x) - 1];
        return;
      }
    });
    return res;
  }

  optional<T> le(const T x) {
    optional<T> res = nullopt;
    for_each(_a.rbegin(), _a.rend(), [&](const auto& a) {
      if (a[0] <= x) {
        res = a[_bisect_right(a, x) - 1];
        return;
      }
    });
    return res;
  }

  optional<T> gt(const T x) {
    optional<T> res = nullopt;
    for (auto &a: _a) {
      if (a.back() > x) {
        res = a[_bisect_right(a, x)];
      }
    }
    return res;
  }

  optional<T> ge(const T x) {
    optional<T> res = nullopt;
    for (auto &a: _a) {
      if (a.back() >= x) {
        res = a[_bisect_left(a, x)];
      }
    }
    return res;
  }

  T get(int i) {
    if (i < 0) {
      for_each(_a.rbegin(), _a.rend(), [&](const auto&& a) {
        i += (int)a.size();
        if (i >= 0) return a[i];
      });
    } else {
      for (const auto &a: _a) {
        if (i < (int)a.size()) return a[i];
        i -= (int)a.size();
      }
    }
    throw out_of_range("Index out of range");
  }

  T pop(int i=-1) {
    if (i < 0) {
      for_each(_a.rbegin(), _a.rend(), [&](const auto&& a) {
        i += (int)a.size();
        if (i >= 0) return _pop(a, i);
      });
    } else {
      for (const auto &a: _a) {
        if (i < (int)a.size()) return _pop(a, i);
        i -= (int)a.size();
      }
    }
    throw out_of_range("Index out of range");
  }

  int index(const T x) {
    int ans = 0;
    for (const auto &a: _a) {
      if (a.back() >= x) {
        return ans + _bisect_left(a, x);
      }
      ans += (int)a.size();
    }
    return ans;
  }

  int index_right(const T x) {
    int ans = 0;
    for (const auto &a: _a) {
      if (a.back() > x) {
        return ans + bisect_right(a, x);
      }
      ans += (int)a.size();
    }
    return ans;
  }

  void print() {
    cout << '{';
    for (const auto &a: _a) {
      for (const auto &aa: a) {
        cout << aa << ", ";
      }
    }
    cout << '}' << endl;
  }
};
