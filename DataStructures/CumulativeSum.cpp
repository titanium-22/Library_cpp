template<typename T>
struct CumulativeSum {
  int _n;
  T _e;
  vector<T> _acc;

  CumulativeSum(vector<T> &a, T e) {
    _n = (int)a.size();
    _acc.resize(_n+1, e);
    for (int i = 0; i < _n; ++i) {
      _acc[i+1] = _acc[i] + a[i];
    }
  }

  T pref(int r) {
    return _acc[r];
  }

  T all_sum() {
    return _acc.back();
  }

  T sum(int l, int r) {
    return _acc[r] - _acc[l];
  }

  T prod(int l, int r) {
    return sum(l, r);
  }

  T all_prod() {
    return all_sum();
  }

  void print() {
    cout << '[';
    for (int i = 0; i < _n; ++i) {
      cout << _acc[i] << ' ';
    }
    cout << _acc.back() << ']' << endl;
  }
};

