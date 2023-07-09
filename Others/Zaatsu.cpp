template<typename T>
struct Zaatsu {
  vector<T> _to_origin;
  map<T, int> _to_zaatsu;
  int n;

  Zaatsu(vector<T> used) {
    sort(used.begin(), used.end());
    used.erase(unique(used.begin(), used.end()), used.end());
    n = (int)used.size();
    _to_origin = used;
    for (int i = 0; i < n; ++i) {
      _to_zaatsu[used[i]] = i;
    }
  }

  int to_zaatsu(T x) {
    return _to_zaatsu[x];
  }

  T to_origin(int x) {
    return _to_origin[x];
  }

  int len() {
    return n;
  }
};
