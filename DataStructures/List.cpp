template<typename T>
struct List {

  vector<T> a;

  List() {}

  List(int n) {
    a.resize(n);
  }

  List(int n, T key) {
    a.resize(n, key);
  }

  List(vector<T> v) {
    a.resize((int)v.size());
    for (int i = 0; i < (int)v.size(); ++i) {
      a[i] = v[i];
    }
  };

  void append(T key) {
    a.emplace_back(key);
  }

  void resize(int n, T e) {
    a.resize(n, e);
  }

  void reserve(int n) {
    a.reserve(n);
  }

  T sum(T e) {
    T res = e;
    for (int i = 0; i < len(); ++i) {
      res += a[i];
    }
    return res;
  }

  void sort(bool reverse=false) {
    if (reverse) {
      std::sort(a.rbegin(), a.rend());
    } else {
      std::sort(a.begin(), a.end());
    }
  }
  
  int index(T key) {
    for (int i = 0; i < len(); ++i) {
      if (a[i] == key) return i;
    }
    return -1;
  }

  int count(T key, int start=-1, int stop=-1) {
    start = start == -1? 0 : start;
    stop = stop == -1? len() : stop;
    if (start < 0) start = 0;
    if (stop > len()) start = len();
    int res = 0;
    for (int i = start; i < stop; ++i) {
      if (a[i] == key) ++res;
    }
    return res;
  }

  void clear() {a.clear();}

  void insert(int i, T key) {
    a.insert(a.begin()+1, key);
  }

  T pop(int i=-1) {
    T key = a[i<0? i+len(): i];
    remove(key);
    return key;
  }

  void remove(T key) {
    std::remove(a.begin(), a.end(), key);
  }

  void reverse() {
    int n = len();
    for (int i = 0; i < n/2; ++i) {
      swap(a[i], a[n-i-1]);
    }
  }

  bool contains(T key) {
    for (int i = 0; i < len(); ++i) {
      if (a[i] == key) return true;
    }
    return false;
  }

  T& operator[] (int i) {
    return a[i<0? i+len(): i];
  }

  T operator[] (int i) const {
    return a[i<0? i+len(): i];
  }

  int len() {
    return (int)a.size();
  }

  vector<T> tovector() {
    vector<T> res = a;
    return res;
  }

  void print() {
    cout << "[";
    for (int i = 0; i < len()-1; ++i) {
      cout << a[i] << ", ";
    }
    if (len() > 0) {
      cout << a.back();
    }
    cout << "]\n";
  }

  void pprint(string sep=" ", string end="\n") {
    for (int i = 0; i < len()-1; ++i) {
      cout << a[i] << sep;
    }
    if (len() > 0) {
      cout << a.back();
    }
    cout << end;
  }
};

